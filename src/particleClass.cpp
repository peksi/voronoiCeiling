//
//  particleClass.cpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#include "particleClass.hpp"

Particle::Particle(ofVec2f _location, float _spawnSpeed) {
    particleColor = ofColor::fromHsb(ofRandom(0,255), 255, 255);
    particleMass = ofRandom(1,4);
    
    location.set(_location.x,_location.y);
    ofVec2f direction = ofVec2f(ofRandom(-1,1),ofRandom(-1,1));
    direction.normalize();
    velocity = direction * _spawnSpeed;
}
void Particle::attract(ofVec2f _attractorCentroid, float _attractorMass) {
    ofVec2f force = _attractorCentroid - location;
    float speed = _attractorCentroid.distance(location);
    float attractionRadius = speed;
    
    if (attractionRadius < 1000) {
        speed = ofClamp(speed, 1, 5);
        force.normalize();
        
        float strength = (1 * _attractorMass * particleMass) / (speed*speed) * (1/speed);
        force *= strength;
        
        applyForce(force);
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
void Particle::display() {
    ofSetColor(particleColor);
    ofDrawCircle(location.x, location.y, 5);
}
