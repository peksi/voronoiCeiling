#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(40);
    ofSetFrameRate(30);
    
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
    
    edgeLineFlag = false;
    
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
    ofBackground(0);
    
    if(voronoi.initialized && voronoi.showVoronoi){
		voronoi.draw(edgeLine);
    }

	voronoi.attractorSystem.displayAttractors();
	voronoi.particleSystem.displayParticles();
    
    // voronoi edge line
    if(voronoi.attractorSystem.showAttractorEdge){
		// set edgeline color first
		ofSetColor(255, 0, 255);
		for (int i = 0; i < edgeLine.size(); i++) {
			edgeLine[i].draw();
		}
		tempEdgeLine.draw();
        
    }
    
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
    } else if (key == 'l'){ // toggle edgeline and make it complete
        if(edgeLineFlag){ // close edgeline
            tempEdgeLine.addVertex(tempEdgeLine.getVertices()[0]);
			edgeLine.push_back(tempEdgeLine);
            // clear tempEdgeline
			tempEdgeLine.clear();
			edgeLineFlag = false;
            // and initialize the voronoi inside the blob
           	//voronoi.initialize(edgeLine);
            
        } else { // if there is no blob just continue
            edgeLineFlag = !edgeLineFlag;
            cout << "Start drawing new edgeblob";
        }
	}
	else if (key == 'i') {
		if (voronoi.initialized) {
			voronoi.destroy();
		}
		voronoi.initialize(edgeLine);
	}
	else if (key == 'u') {
		cout << "Undo one edgeLoop";
		edgeLine.pop_back();
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
    if(edgeLineFlag) {
        ofPoint pt;
        pt.set(x, y);
        tempEdgeLine.addVertex(pt);
    } else {
		// cout << "Trying to add new attractor point";
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
