//
//  particleClass.hpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#ifndef particleClass_hpp
#define particleClass_hpp

#include "ofMain.h"

class Particle {
public:
    void attract(ofVec2f _attractorCentroid, float _attractorMass);
    void checkLocation(ofPolyline _attractorPoly);
    bool checkDead();
    void applyForce(ofVec2f _force);
    void update(float _velocityLimit);
    void display();
    
    ofVec2f location;
    ofVec2f acceleration;
    ofVec2f velocity;
    
    bool isDead;
    
    ofColor particleColor;
    float particleMass;
    
    Particle(ofVec2f _location, float _spawnSpeed);
};

#endif /* particleClass_hpp */
