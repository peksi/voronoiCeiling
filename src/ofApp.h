#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxVoro.h"

#include "particleSystem.hpp"
#include "attractorClass.hpp"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    bool guiHide;
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void makeTissue(int _nCells, int _width, int _height, int _deep);
        
    // void circleResolutionChanged(int & circleResolution);
    
    ofxPanel gui;
    ofxColorSlider color;
    ofxIntSlider grainSize;
    ofxToggle voronoi;
    ofxToggle addParticles;

    // ofxIntSlider resolution;
    
    // particles
    ParticleSystem particleSystem;
    vector<Attractor> attractorVector;
    
    float distance;
    int attractorIndex;
    int cornerIndex;
    
    //voronoi
    vector<glm::vec3> cellCentroids;
    vector<float>   cellRadius;
    vector<ofVboMesh>  cellMeshes;
    vector<ofVboMesh>  cellMeshWireframes;
};
