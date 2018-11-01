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
