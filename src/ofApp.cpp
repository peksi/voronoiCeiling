#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
    ofSetFrameRate(50);
    

    // gui setup
    guiHide = false;
    gui.setup("GUI");
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(grainSize.setup("grain size", 100, 10, 1000));
    gui.add(voronoi.setup("draw voronoi", false));
    gui.add(addParticles.setup("add particles", false));
    

    // magic
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    // the voronoi pattern itself

    voronoipattern.makeTissue(50, ofGetHeight()*0.8, ofGetHeight()*0.8, 20);

}

//--------------------------------------------------------------
void ofApp::update(){
    // General settings
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // Particle system
    if (ofGetFrameNum()%1 == 0 && addParticles) {
        particleSystem.addParticles(1,5);
    }
    
    for (int i = 0; i < attractorVector.size(); i++) {
        particleSystem.attractParticles(attractorVector[i].attractorCentroid,
                                        attractorVector[i].attractorMass);
    }
    particleSystem.checkLocation(attractorVector); // checks if particle should be removed
    particleSystem.edgeDetect();
    particleSystem.updateParticles();
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    // draw voronoi
    if(voronoi){
        voronoipattern.draw();
    }
    
    
    // particle system
    particleSystem.displayParticles();
    
    for (int i = 0; i < attractorVector.size(); i++) {
        attractorVector[i].display();
    }
    
    
    // gui
    if(!guiHide){
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == 'f'){
        ofToggleFullscreen();
    } else if ( key == 'h'){ // hide gui
        guiHide = !guiHide;
    } else if ( key == 'p'){ // particle attractor
        int vectorSize = attractorVector.size();
        if (vectorSize >= 1) {
            if (attractorVector[attractorVector.size()-1].fullySet == true) {
                attractorVector.push_back(*new Attractor);
                
            }
        } else {
            attractorVector.push_back(*new Attractor); // Init first attractor
        }
    } else {
        voronoipattern.makeTissue(grainSize, ofGetWidth()*0.8, ofGetHeight()*0.8,20);
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
    for (int i = 0; i < attractorVector.size(); i++) {
        if (attractorVector[i].fullySet == true) {
            
            for (int j = 0; j < attractorVector[i].cornerPoints.size(); j++) {
                float tempDist = attractorVector[i].cornerPoints[j].distance(ofVec2f(ofGetMouseX(),ofGetMouseY()));
                if (tempDist < distance) {
                    distance = tempDist;
                    attractorIndex = i;
                    cornerIndex = j;
                }
            }
            
            if (distance < 20) {
                attractorVector[attractorIndex].changeCornerPoint(cornerIndex);
                attractorVector[attractorIndex].activateCornerPoint(cornerIndex, true);
            }
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (attractorVector.size() != 0) {
        for (int i = 0; i < attractorVector.size(); i++) {
            if (attractorVector[i].editState == true && attractorVector[i].fullySet == false) {
                attractorVector[i].setCornerPoints();
            }
        }
        for (int j = 0; j < 4; j++) {
            attractorVector[attractorIndex].activateCornerPoint(j, false);
        } // Reset all activated cornerpoints
        
        attractorVector[attractorIndex].updateShape(); // Update shape after moving points
        distance = ofGetWidth(); // Reset for next changeCornerPoint.
        attractorIndex = 0; // Reset for next changeCornerPoint.
        cornerIndex = 0; // Reset for next changeCornerPoint.
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
