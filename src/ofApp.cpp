#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
    // ofSetFrameRate(60);
    
    // Graphics setup
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    // Init setup
    lastTime = ofGetElapsedTimef();
    
    // GUI setup
    particleGroup.add(particleSystem.particleParameters);
    particleGui.setup("Particle GUI panel");
    particleGui.setDefaultWidth(int(ofGetWidth()/4));
    particleGui.setup(particleGroup);
    
    attractorGroup.add(attractorSystem.attractorParameters);
    attractorGui.setup("Attractor GUI panel");
    attractorGui.setDefaultWidth(int(ofGetWidth()/4));
    attractorGui.setup(attractorGroup);
    attractorGui.setPosition(particleGui.getPosition().x,
                             particleGui.getPosition().y+particleGui.getHeight() + 20);
    
    // Voronoi setup. Might go elsewhere
    
    //  Add the cell seed to the container
    int nCells = 300;
    vector<glm::vec2> _points;
    for(int i = 0; i < nCells;i++){
        glm::vec2 newPoint = glm::vec2(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        _points.push_back(newPoint);
    }
    
    relaxedVoronoi.setBounds(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
    relaxedVoronoi.setPoints(_points);
    relaxedVoronoi.generate();
    
    voronoiCentroids = relaxedVoronoi.getPoints();
    
    int relaxIterations = 10;
    while(relaxIterations--){
        relaxedVoronoi.relax();
    }
    
    // VBO construction
    vector<ofxVoronoiCell> tempCells = relaxedVoronoi.getCells();
    for (int i = 0; i < tempCells.size() ; i++) {
        vector<glm::vec2> tempCell = tempCells[i].pts;
        
        vector<ofVec3f> tempCell3d;
        vector<ofIndexType> tempIndices;
        vector<ofFloatColor> tempColors;
        
        for(int j = 0; j < tempCell.size(); j++){
            tempCell3d.push_back(ofVec3f(tempCell[j].x, tempCell[j].y, 0.0f));
            tempColors.push_back(ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0),1.0));
            tempIndices.push_back(j);
        }
        
        vboVerts.push_back(tempCell3d);
        vboFaces.push_back(tempIndices);
        vboColor.push_back(tempColors);
    }
    
    for (int i = 0; i < vboVerts.size(); i++) {
        vboVector.push_back(*new ofVbo); // Free up slot for this VBO
        vboVector[i].setVertexData( &vboVerts[i][0], vboVerts[i].size(), GL_STATIC_DRAW );
        vboVector[i].setIndexData( &vboFaces[i][0], vboVerts[i].size(), GL_STATIC_DRAW );
        vboVector[i].setColorData( &vboColor[i][0], vboVerts[i].size(), GL_DYNAMIC_DRAW );
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // GENERAL SETTINGS
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // PARTICLE SYSTEM
    // Timer system to iterate over dispersing attractors
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastTime > 2) {
        attractorSystem.activateAttractor();
        lastTime = currentTime;
    }
    
    // For loop needed for functions that check [particle <-> attractor] relations.
    for (int i = 0; i < attractorSystem.attractorVector.size(); i++) {
        if (attractorSystem.attractorVector[i].active == false) {
            particleSystem.addParticles(attractorSystem.attractorVector[i].attractorCentroid,
                                        1, 5);
        }
        if (attractorSystem.attractorVector[i].active == true) {
            particleSystem.checkLocation(attractorSystem.attractorVector[i].attractorPoly);
            particleSystem.attractParticles(attractorSystem.attractorVector[i].attractorCentroid,
                                            attractorSystem.attractorVector[i].attractorMass,
                                            1000);
        }
    }
    particleSystem.edgeDetect();
    particleSystem.updateParticles();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    // VBO
    for (int i = 0; i < vboVector.size();i++) {
        glPointSize(10.f);
        vboVector[i].drawElements(GL_POLYGON, vboVerts[i].size()); // placeholder values
    }
    
    // particle system
    particleSystem.displayParticles();
    attractorSystem.displayAttractors();
    
    // Checking system
    for (int i = 0; i < voronoiCentroids.size(); i++) {
        for (int j = 0; j < particleSystem.particleVector.size(); j++) {
            glm::vec2 tempCentroid = voronoiCentroids[i];
            Particle tempParticle = particleSystem.particleVector[j];
            
            ofVec2f centroidLocation = ofVec2f(tempCentroid.x,tempCentroid.y);
            ofVec2f particleLocation = ofVec2f(tempParticle.location.x,tempParticle.location.y);
            
            float centroidDistance = centroidLocation.distance(particleLocation);
            
            if (centroidDistance < 50) {
                int nearestVertex = 0;
                int vertexDistanceHolder = 50;
                for (int k = 0; k < vboVerts[i].size(); k++) {
                    ofVec2f VertexLocation = ofVec3f(vboVerts[i][k].x, vboVerts[i][k].y);
                    float vertexDistance = VertexLocation.distance(particleLocation);
                    
                    if (vertexDistance < vertexDistanceHolder) {
                        vertexDistanceHolder = vertexDistance;
                        nearestVertex = k;
                    }
                    
                    vboColor[i][k] = ofFloatColor(ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0),1.0));
                    vboVector[i].updateColorData(&vboColor[i][0], vboVerts[i].size());
                }
            }
        }
    }
    
    // gui
    if(!guiHide){
        particleGui.draw();
        attractorGui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == 'f'){
        ofToggleFullscreen();
    } else if ( key == 'h'){ // hide gui
        guiHide = !guiHide;
    } else if (key == 'p') {
        attractorSystem.createAttractor();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    attractorSystem.moveAttractorPoints();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    attractorSystem.setAttractor();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
