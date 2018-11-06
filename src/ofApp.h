#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "particleSystem.hpp"
#include "attractorClass.hpp"
#include "voronoi.h"

class ofApp : public ofBaseApp{
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
    
    VoronoiTissue voronoipattern;
    
    // particles
    ParticleSystem particleSystem;
    vector<Attractor> attractorVector;
    
    float distance;
    int attractorIndex;
    int cornerIndex;
    
    ofxPanel particleGui, attractorGui;
    ofParameterGroup particleGroup;
    ofParameterGroup attractorGroup;
    ofParameter<bool> showAttractorEdge,showAttractorPoints,showAttractorFill;
    
};
