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
    
    // particle system
    particleSystem.displayParticles();
    attractorSystem.displayAttractors();
    
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
