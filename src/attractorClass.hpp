//
//  attractorClass.hpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#ifndef attractorClass_hpp
#define attractorClass_hpp

#include "ofMain.h"
#include "particleClass.hpp"

class Attractor {
public:
    void activateCornerPoint(int _pointIndex, bool _state);
    void changeCornerPoint(int _pointIndex);
    void setCornerPoints();
    void updateShape();
    void attract(vector<Particle> _particleVector);
    void display(bool _showEdge, bool _showPoints, bool _showFill);
    
    bool active; // Is this attractor currently attracting particles
    
    vector<ofVec2f> cornerPoints; // Vector of 4 cornerpoints
    vector<bool> cornerState; // checking if point is in edit mode
    int cornerCount; // Check which is the next point to set
    bool editState, fullySet;
    
    ofPolyline attractorPoly; // Needed for shape outline & centroid calculation
    ofPath attractorShape; // Needed for shape fill
    ofVec2f attractorCentroid;
    
    float attractorMass;
    
    Attractor();
};

#endif /* attractorClass_hpp */
