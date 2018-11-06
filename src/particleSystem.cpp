//
//  particleSystem.cpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#include "particleSystem.hpp"

ParticleSystem::ParticleSystem() {
    particleParameters.setName("Particle GUI panel");
    particleParameters.add(spawnParticles.set("Spawn particles",false));
    particleParameters.add(guiListener.set("Particles listen to GUI controls",false));
    particleParameters.add(particleCount.set("Particle count per emit",1,0,100));
    particleParameters.add(particleSpawnSpeed.set("Particle spawn speed",5,0,50));
    particleParameters.add(velocityLimit.set("Particle velocity limit",5,0,50));
    particleParameters.add(attractorsForce.set("Attractor force",1,0,10));
    particleParameters.add(attractorsRadius.set("Attractor radius",1000,0,4000));
    particleParameters.add(edgeRepel.set("Repel particles from edge",true));
    particleParameters.add(showParticles.set("Display particles",true));
    particleParameters.add(deleteParticles.set("Remove particles by attractor",true));
}
void ParticleSystem::addParticles(int _count,float _spawnSpeed) {
    int count;
    float spawnSpeed;
    
    if (guiListener == true) {
        count = particleCount;
        spawnSpeed = particleSpawnSpeed;
    } else {
        count = _count;
        spawnSpeed = _spawnSpeed;
    }
    
    if (spawnParticles == true) {
        for (int i = 0; i < count; i++) {
            particleVector.push_back(*new Particle(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),spawnSpeed));
        }
    }
    
}
void ParticleSystem::removeParticles() {
    bool activeParticleRemove;
    
    if (guiListener == true) {
        activeParticleRemove = deleteParticles;
    } else {
        activeParticleRemove = true;
    }
    
    if (activeParticleRemove == true) {
        for(vector<Particle>::iterator particleIterator = particleVector.begin();
            particleIterator != particleVector.end();){
            
            if ((*particleIterator).isDead) {
                particleVector.erase(particleIterator);
            } else {
                ++particleIterator;
            }
        }
    }
}
void ParticleSystem::edgeDetect() {
    bool activeEdgeDetect;
    
    if (guiListener == true) {
        activeEdgeDetect = edgeRepel;
    } else {
        activeEdgeDetect = true;
    }
    
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].edgeDetect();
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
void ParticleSystem::attractParticles(ofVec2f _attractorCentroid, float _attractorForce, float _attractionRadius) {
    
    
    float attractorForce;
    float attractionRadius;
    
    if (guiListener == true) {
        attractorForce = attractorsForce;
        attractionRadius = attractorsRadius;
    } else {
        attractorForce = _attractorForce;
        attractionRadius = _attractionRadius;
    }
    
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].attract(_attractorCentroid,_attractorForce,_attractionRadius);
    }
}
void ParticleSystem::updateParticles() {
    for (int i = 0; i < particleVector.size(); i++) {
        particleVector[i].update(velocityLimit);
    }
}
void ParticleSystem::displayParticles() {
    bool activeParticleDisplay;
    
    if (guiListener == true) {
        activeParticleDisplay = showParticles;
    } else {
        activeParticleDisplay = true;
    }
    
    if (activeParticleDisplay == true) {
        for (int i = 0; i < particleVector.size(); i++) {
            particleVector[i].display(showParticles);
        }
    }
    
}
