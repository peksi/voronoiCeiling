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
    void attract(ofVec2f _attractorCentroid, float _attractorMass,int _attractionRadius);
    void checkLocation(ofPolyline _attractorPoly);
    void edgeDetect();
    void applyForce(ofVec2f _force);
    void update(float _velocityLimit);
    void display(bool _showParticle);
    
    ofVec2f location;
    ofVec2f acceleration;
    ofVec2f velocity;
    
    bool isDead;
    
    ofColor particleColor;
    bool particleColorChoice;
    float particleMass;
    
    Particle(ofVec2f _location, float _spawnSpeed);
};

#endif /* particleClass_hpp */
