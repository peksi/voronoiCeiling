#include "ofMain.h"
#include "ofxGui.h"
#include "ofxVoronoi.h"
#include "particleSystem.hpp"
#include "attractorSystem.hpp"

class Voronoi {
public:
    void initialize(vector<ofPolyline> bounds);
    bool initialized;
    void draw(vector<ofPolyline> bounds);
    
    // ParticleSystem
    ParticleSystem particleSystem;
    // AttractorSystem
    AttractorSystem attractorSystem;
    
    
    // gui parameters
    ofParameterGroup voronoiParameters;
    ofParameter<bool> showVoronoi;
    ofParameter<bool> backgroundColorSet;
    
    // VBO
    vector<ofVbo> vboVector;
    vector<vector<ofVec3f>> vboVerts;
    vector<vector<ofIndexType>> vboFaces;
    vector<vector<ofFloatColor>> vboColor;
    
    // Voronoi
    ofxVoronoi relaxedVoronoi;
    
    vector<glm::vec2> voronoiCentroids;
    
    Voronoi();
};
