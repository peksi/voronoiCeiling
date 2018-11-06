//
//  attractorSystem.hpp
//  voronoiCeiling2
//
//  Created by Robbert Groenendijk on 06/11/2018.
//

#ifndef attractorSystem_hpp
#define attractorSystem_hpp

#include "ofMain.h"
#include "ofxGui.h"

#include "attractorClass.hpp"

class AttractorSystem {
public:
    void createAttractor();
    void setAttractor();
    void moveAttractorPoints();
    void displayAttractors();
    
    vector<Attractor> attractorVector;
    
    float distance;
    int attractorIndex;
    int cornerIndex;
    
    ofParameterGroup attractorParameters;
    ofParameter<bool> showAttractorEdge,showAttractorPoints,showAttractorFill;
    
    AttractorSystem();
};

#endif /* attractorSystem_hpp */
