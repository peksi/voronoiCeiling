#include "ofApp.h"

ofFloatColor c[] = {
    ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0)),
    ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0)),
    ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0)),
    ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0)),
    ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0)),
};

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
    ofSetFrameRate(50);
    
    // Graphics setup
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    //glEnable(GL_DEPTH_TEST);
    
    
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
    
    // Voronoi setup.
    // Add the cell seed to the container
    /*
    int nCells = 100;
    vector<glm::vec2> _points;
    for(int i = 0; i < nCells;i++){
        glm::vec2 newPoint = glm::vec2(
                                       ofRandom(0,ofGetWidth()),
                                       ofRandom(0,ofGetHeight())
                                       );
        
        _points.push_back(newPoint);
    }
    relaxedVoronoi.setBounds(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
    relaxedVoronoi.setPoints(_points);
    relaxedVoronoi.generate();
    
    int relaxIterations = 10;
    while(relaxIterations--){
        relaxedVoronoi.relax();
    }
    
    curve = true;
    relaxedVoronoi.draw(true);
     */
    const ofVec3f Verts[] = {
        ofVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0.0),
        ofVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0.0),
        ofVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0.0),
        ofVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0.0),
        ofVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0.0),
    };
    const ofIndexType Faces[] = {0,1,2,3,4};
    
    int vboCount = 10;
    for (int i = 0; i < vboCount; i++) {
        vboVector.push_back(*new ofVbo); // Free up slot for this VBO
        vboVector[i].setVertexData( &Verts[0], 5, GL_STATIC_DRAW );
        vboVector[i].setColorData( &c[0], 5, GL_DYNAMIC_DRAW );
        vboVector[i].setIndexData( &Faces[0], 5, GL_STATIC_DRAW );
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
    // voronoi
    /*
    for(int i=0; i < voronois.size(); i++){
        voronois[i].draw();
    }
     */
    
    // VBO
    for (int i = 0; i < vboVector.size();i++) {
        for (int j = 0; j < particleSystem.particleVector.size(); j++) {
            for (int x = 0; x < 5; x++) {
                c[x] = ofFloatColor(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0));
            }
        }
    }

    for (int i = 0; i < vboVector.size();i++) {
        glPointSize(10.f);
        vboVector[i].updateColorData(&c[0], 5);
        vboVector[i].drawElements(GL_TRIANGLES, 60); // placeholder values
    }
    
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
    } else if (key == 's') {
        particleSystem.toggleParticles();
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
