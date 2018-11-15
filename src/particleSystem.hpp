//
//  particleSystem.hpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#ifndef particleSystem_hpp
#define particleSystem_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "particleClass.hpp"
#include "attractorClass.hpp"

class ParticleSystem {
public:
    void addParticles(ofVec2f _attractorCentroid,int _count, float _spawnSpeed);
    void removeParticles();
    bool checkDead(Particle &p);
    void attractParticles(ofVec2f _attractorCentroid, float _attractorForce,float _attractionRadius);
    void edgeDetect();
    void checkLocation(ofPolyline _attractorPoly);
    void updateParticles();
    void displayParticles();
    
    vector<Particle> particleVector;
    
    ofParameterGroup particleParameters;
    ofParameter<int> particleCount;
    ofParameter<float> particleSpawnSpeed;
    ofParameter<float> velocityLimit;
    ofParameter<float> attractorsForce;
    ofParameter<float> attractorsRadius;
    ofParameter<bool> spawnParticles,edgeRepel, showParticles,deleteParticles, guiListener, particleDebug;
    
    ParticleSystem();
};

#endif /* particleSystem_hpp */
