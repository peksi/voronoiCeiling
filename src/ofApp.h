#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "particleSystem.hpp"
#include "attractorSystem.hpp"
#include "attractorClass.hpp"
#include "voronoi.hpp"




class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    
    bool guiHide;
    bool curve;
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // Public variables
    float lastTime;
    
    Voronoi voronoi;
    
    // voronoi edge line
    
    vector<ofPolyline> edgeLine;
	ofPolyline tempEdgeLine;
    bool edgeLineFlag;
    
    // GUI
    ofxPanel particleGui, attractorGui, voronoiGui;
    ofParameterGroup particleGroup;
    ofParameterGroup attractorGroup;
    ofParameterGroup voronoiGroup;
    
    
};
