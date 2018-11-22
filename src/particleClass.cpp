//
//  particleClass.cpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#include "particleClass.hpp"

Particle::Particle(ofVec2f _location, float _spawnSpeed) {
    particleColor = ofColor::fromHsb(ofRandom(0,255), 255, 255);
    
    if (ofRandom(0,1) >= 0.5) {
        particleColorChoice = false;
    } else {
        particleColorChoice = true;
    }
    
    particleMass = ofRandom(1,4);
    
    location.set(_location.x,_location.y);
    ofVec2f direction = ofVec2f(ofRandom(-1,1),ofRandom(-1,1));
    direction.normalize();
    velocity = direction * _spawnSpeed;
}
void Particle::edgeDetect() {
    if (location.x < 0 + 50) {
        if (velocity.x < 0) {
            float distance = location.x;
            float forceStrength = 1 / distance;
            float pushForceX = velocity.x;
            pushForceX = pushForceX * -forceStrength;
            applyForce(ofVec2f(pushForceX,0.0));
        }
    }
    if (location.x > ofGetWidth() - 50) {
        if (velocity.x > 0) {
            float distance = ofGetWidth() - location.x;
            float forceStrength = 1 / distance;
            float pushForceX = velocity.x;
            pushForceX = pushForceX * -forceStrength;
            applyForce(ofVec2f(pushForceX,0.0));
        }
    }
    if (location.y < 0 + 50) {
        if (velocity.y < 0) {
            float distance = location.y;
            float forceStrength = 1 / distance;
            float pushForceY = velocity.y;
            pushForceY = pushForceY * -forceStrength;
            applyForce(ofVec2f(0.0,pushForceY));
        }
    }
    if (location.y > ofGetHeight() - 50) {
        if (velocity.y > 0) {
            float distance = ofGetHeight() - location.y;
            float forceStrength = 1 / distance;
            float pushForceY = velocity.y;
            pushForceY = pushForceY * -forceStrength;
            applyForce(ofVec2f(0.0,pushForceY));
        }
    }
    
    if (location.x < 0) {
        location.x = 0;
    }
    if (location.x > ofGetWidth()) {
        location.x = ofGetWidth();
    }
    if (location.y < 0) {
        location.y = 0;
    }
    if (location.y > ofGetHeight()) {
        location.y = ofGetHeight();
    }
    
    // Kill particle if accidental leave
    if (location.x < 0-100) {
        isDead = true;
    }
    if (location.x > ofGetWidth() + 100) {
         isDead = true;
    }
    if (location.y < 0 - 100) {
         isDead = true;
    }
    if (location.y > ofGetHeight() + 100) {
         isDead = true;
    }
}
void Particle::attract(ofVec2f _attractorCentroid, float _attractorMass,int _attractionRadius) {
    ofVec2f force = _attractorCentroid - location;
    float dist = _attractorCentroid.distance(location);
    float attractionRadius = _attractionRadius;
    
    if (dist < attractionRadius) {
        float speed = ofClamp(dist, 1, 5);
        force.normalize();
        
        float strength = (5 * _attractorMass * particleMass) / (speed*speed) * (1/speed);
        force *= strength;
        
        applyForce(force);
    } else {
        // This code is to make sure that there is always a force.
        // this way particles don't get stuck.
        force.normalize();
        applyForce(force/1000);
    }
}
void Particle::applyForce(ofVec2f _force) {
    acceleration += _force;
}
void Particle::update(float _velocityLimit) {
    velocity += acceleration;
    location += velocity;
    velocity.limit(_velocityLimit);
    
    acceleration *= 0; // reset acceleration after frame
}
void Particle::display(bool _showParticle) {
    if (_showParticle == true) {
        ofSetColor(particleColor);
        ofDrawCircle(location.x, location.y, 5);
    }
}
