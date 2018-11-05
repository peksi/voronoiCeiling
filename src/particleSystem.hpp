//
//  particleSystem.hpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#ifndef particleSystem_hpp
#define particleSystem_hpp

#include "ofMain.h"
#include "particleClass.hpp"
#include "attractorClass.hpp"

class ParticleSystem {
public:
    void addParticles(int _count, float _spawnSpeed);
    void removeParticles();
    bool checkDead(Particle &p);
    void attractParticles(ofVec2f _attractorCentroid, float _attractorForce);
    void checkLocation(vector<Attractor> _attractorVector);
    void updateParticles();
    void displayParticles();
    
    vector<Particle> particleVector;
    
    ParticleSystem();
};

#endif /* particleSystem_hpp */
