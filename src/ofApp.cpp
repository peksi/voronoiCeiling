#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
    ofSetFrameRate(50);
    
    // Graphics setup
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    // Init setup
    lastTime = ofGetElapsedTimef();
    
    // GUI setup
    particleGroup.add(voronoi.particleSystem.particleParameters);
    particleGui.setup("Particle GUI panel");
    particleGui.setDefaultWidth(int(ofGetWidth()/4));
    particleGui.setup(particleGroup);
    
    attractorGroup.add(voronoi.attractorSystem.attractorParameters);
    attractorGui.setup("Attractor GUI panel");
    attractorGui.setDefaultWidth(int(ofGetWidth()/4));
    attractorGui.setup(attractorGroup);
    attractorGui.setPosition(particleGui.getPosition().x,
                             particleGui.getPosition().y+particleGui.getHeight() + 20);
    
    voronoiGroup.add(voronoi.voronoiParameters);
    voronoiGui.setup("Voronoi GUI panel");
    voronoiGui.setDefaultWidth(int(ofGetWidth()/4));
    voronoiGui.setup(voronoiGroup);
    voronoiGui.setPosition(attractorGui.getPosition().x,
                             attractorGui.getPosition().y+attractorGui.getHeight() + 20);
    
    edgeLineFlag = true;
    
    // mockup bounds for now
    // todo: initialize voronoi after bounds are created and move this function to elsewhere
    glm::vec2 bounds = glm::vec2(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
    voronoi.initialize(bounds);
}

//--------------------------------------------------------------
void ofApp::update(){
    // GENERAL SETTINGS
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // PARTICLE SYSTEM
    // Timer system to iterate over dispersing attractors
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastTime > 5) {
        voronoi.attractorSystem.activateAttractor();
        lastTime = currentTime;
    }
    
    // For loop needed for functions that check [particle <-> attractor] relations.
    for (int i = 0; i < voronoi.attractorSystem.attractorVector.size(); i++) {
        if (voronoi.attractorSystem.attractorVector[i].active == false) {
            voronoi.particleSystem.addParticles(voronoi.attractorSystem.attractorVector[i].attractorCentroid,
                                        1, 5);
        }
        if (voronoi.attractorSystem.attractorVector[i].active == true) {
            voronoi.particleSystem.checkLocation(voronoi.attractorSystem.attractorVector[i].attractorPoly);
            voronoi.particleSystem.attractParticles(voronoi.attractorSystem.attractorVector[i].attractorCentroid,
                                            voronoi.attractorSystem.attractorVector[i].attractorMass,
                                            1000);
        }
    }
    voronoi.particleSystem.edgeDetect();
    voronoi.particleSystem.updateParticles();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    
    voronoi.draw();
    
    // voronoi edge line
    edgeLine.draw();
    
    // gui
    if(!guiHide){
        particleGui.draw();
        attractorGui.draw();
        voronoiGui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == 'f'){
        ofToggleFullscreen();
    } else if ( key == 'h'){ // hide gui
        guiHide = !guiHide;
    } else if (key == 'p') { // create particle attractor
        voronoi.attractorSystem.createAttractor();
    } else if (key == 'l'){ // toggle edgeline
        edgeLineFlag = !edgeLineFlag;
        cout << "edgeLineFlag toggled \n";
        cout << edgeLineFlag;
        cout << '\n';
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
    voronoi.attractorSystem.moveAttractorPoints();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(edgeLineFlag){
        ofPoint pt;
        pt.set(x, y);
        edgeLine.addVertex(pt);
    } else {
        voronoi.attractorSystem.setAttractor();
    }
    
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
