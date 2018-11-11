#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
//    ofSetFrameRate(50);
    
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
    
    int relaxIterations = 10;
    while(relaxIterations--){
        relaxedVoronoi.relax();
    }
    
    curve = false;
    voronois = relaxedVoronoi.draw(curve);
    
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
    // voronoi
    for(int i=0; i < voronois.size(); i++){
        voronois[i].draw();
    }
    
    // particle system
    particleSystem.displayParticles();
    attractorSystem.displayAttractors();
    
    
    // example for getting the centroids
    centroids = relaxedVoronoi.getPoints();
    for(int i = 0; i < centroids.size(); i++){
        ofDrawCircle(centroids[i], 3);
    }
    
    // example for getting the vertexes and drawing one
    vertices = relaxedVoronoi.getCells();
    ofFill();
    ofSetColor(220, 0, 0);
    // draw couple of vertexes just for the sake of it
    ofDrawCircle(vertices[0].pts[0], 10);
    ofDrawCircle(vertices[0].pts[1], 10);
    
    
    
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
