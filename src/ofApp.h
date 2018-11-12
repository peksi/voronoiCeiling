#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "particleSystem.hpp"
#include "attractorSystem.hpp"
#include "attractorClass.hpp"

#include "ofxVoronoi.h"

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

    // ParticleSystem
    ParticleSystem particleSystem;
    // AttractorSystem
    AttractorSystem attractorSystem;
    
    // VBO
    vector<ofVbo> vboVector;
    vector<vector<ofVec3f>> vboVerts;
    vector<vector<ofIndexType>> vboFaces;
    vector<vector<ofFloatColor>> vboColor;
    
    // GUI
    ofxPanel particleGui, attractorGui, voronoiGui;
    ofParameterGroup particleGroup;
    ofParameterGroup attractorGroup;
    ofParameterGroup voronoiGroup;
    
    // Voronoi
    ofxVoronoi relaxedVoronoi;
    //vector<ofPolyline> voronois;
    vector<glm::vec2> voronoiCentroids;
    //vector<ofxVoronoiCell> vertices; // returns glm::vec2 vector
};
