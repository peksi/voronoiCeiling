#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){
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
    
    // light.setPosition(100,500, 100);
    cam.setAutoDistance(true);
    
    // the voronoi pattern itself
    makeTissue(50, ofGetHeight()*0.8, ofGetHeight()*0.8, 20);
}

void testApp::makeTissue(int _nCells, int _width, int _height, int _deep){
    
    //  Fresh begining
    //
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();
    
    //  Define a container
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
    con.add_wall(cyl);
    
    //  Add the cell seed to the container
    for(int i = 0; i < _nCells;i++){
        glm::vec3 newCell = ofVec3f(ofRandom(-_width*0.5,_width*0.5),
                                  ofRandom(-_height*0.5,_height*0.5),
                                  0);
        
        
        addCellSeed(con, newCell, i, true);
    }
    
    cellMeshes = getCellsFromContainer(con,0.0);
    cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    cellRadius = getCellsRadius(con);
    cellCentroids = getCellsCentroids(con);
}

//--------------------------------------------------------------
void testApp::update(){
    // particle system
    if (ofGetFrameNum()%25 == 0 && addParticles) {
        particleSystem.addParticles(1,5);
    }
    
    for (int i = 0; i < attractorVector.size(); i++) {
        particleSystem.attractParticles(attractorVector[i].attractorCentroid,attractorVector[i].attractorMass);
    }
    
    
    particleSystem.updateParticles();
    
    // voronoi
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    
    // voronoi
    ofPushMatrix();
    cam.begin();
    // light.enable();
    // ofEnableLighting();
    glEnable(GL_DEPTH_TEST);
    if(voronoi){
        for(int i = 0; i < cellMeshes.size(); i++){
            ofSetColor(color);
            cellMeshes[i].drawFaces();
            
            ofPushStyle();
            ofSetLineWidth(3);
            ofSetColor(255);
            cellMeshWireframes[i].draw();
            ofPopStyle();
        }
        
    }
    
    glDisable(GL_DEPTH_TEST);
    // ofDisableLighting();
    // light.disable();
    cam.end();
    ofPopMatrix();
    
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
void testApp::keyPressed(int key){
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
        makeTissue(grainSize, ofGetWidth()*0.8, ofGetHeight()*0.8,20);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
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
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
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
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
