//
//  particleSystem.cpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#include "particleSystem.hpp"

ParticleSystem::ParticleSystem() {
    
}
void ParticleSystem::addParticles(int _count,float _spawnSpeed) {
    for (int i = 0; i < _count; i++) {
        particleVector.push_back(*new Particle(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),_spawnSpeed));
    }
}
void ParticleSystem::removeParticles() {
    for(vector<Particle>::iterator particleIterator = particleVector.begin();
        particleIterator != particleVector.end();){
        
        if ((*particleIterator).isDead) {
            particleVector.erase(particleIterator);
        } else {
            ++particleIterator;
        }
    }
}
void ParticleSystem::checkLocation(vector<Attractor> _attractorVector) {
    vector<ofPolyline> attractorPolyVector;
    for (int i = 0; i < _attractorVector.size(); i++) {
        for (int j = 0; j < particleVector.size(); j++) {
            if (_attractorVector[i].attractorPoly.inside(
                                                         particleVector[j].location.x,
                                                         particleVector[j].location.y)) {
                particleVector[j].isDead = true;
            }
        }
    }
    removeParticles(); // This is the only function to kill particles so can call remove after.
}
void ParticleSystem::attractParticles(ofVec2f _attractorCentroid, float _attractorForce) {
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].attract(_attractorCentroid,_attractorForce);
    }
}
void ParticleSystem::updateParticles() {
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].update(3);
    }
}
void ParticleSystem::displayParticles() {
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].display();
    }
}
