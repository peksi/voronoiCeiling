//
//  attractorSystem.cpp
//  voronoiCeiling2
//
//  Created by Robbert Groenendijk on 06/11/2018.
//

#include "attractorSystem.hpp"

AttractorSystem::AttractorSystem() {
    attractorParameters.setName("Attractor GUI panel");
    attractorParameters.add(showAttractorEdge.set("Show attractor edge",true));
    attractorParameters.add(showAttractorPoints.set("Show attractor points", true));
    attractorParameters.add(showAttractorFill.set("Show attractor fill", true));
}
void AttractorSystem::createAttractor() {
    int vectorSize = attractorVector.size();
    
    if (vectorSize >= 1) {
        if (attractorVector[attractorVector.size()-1].fullySet == true) {
            attractorVector.push_back(*new Attractor);
            
        }
    } else {
        attractorVector.push_back(*new Attractor); // Init first attractor
    }
}
void AttractorSystem::setAttractor() {
    if (attractorVector.size() != 0) {
        for (int i = 0; i < attractorVector.size(); i++) {
            if (attractorVector[i].editState == true && attractorVector[i].fullySet == false) {
                attractorVector[i].setCornerPoints();
            }
        }
        for (int j = 0; j < attractorVector.size(); j++) {
            attractorVector[attractorIndex].activateCornerPoint(j, false);
        } // Reset all activated cornerpoints
        
        attractorVector[attractorIndex].updateShape(); // Update shape after moving points
        distance = ofGetWidth(); // Reset for next changeCornerPoint.
        attractorIndex = 0; // Reset for next changeCornerPoint.
        cornerIndex = 0; // Reset for next changeCornerPoint.
    }
}
void AttractorSystem::moveAttractorPoints() {
    for (int i = 0; i < attractorVector.size(); i++) {
        if (attractorVector[i].fullySet == true) {
            
            for (int j = 0; j < attractorVector[i].cornerPoints.size(); j++) {
                float tempDist = attractorVector[i].cornerPoints[j].distance(ofVec2f(ofGetMouseX(),ofGetMouseY()));
                if (tempDist < distance) {
                    distance = tempDist;
                    attractorIndex = i;
                    cornerIndex = j;
                }
            }
            if (distance < 20) {
                attractorVector[attractorIndex].changeCornerPoint(cornerIndex);
                attractorVector[attractorIndex].activateCornerPoint(cornerIndex, true);
            }
        }
    }
}
void AttractorSystem::activateAttractor() {
    int randomPick = int(ofRandom(0.0,attractorVector.size()-1));
    
    // Function to make sure the same attractor isn't chosen again.
    if (randomPick == lastRandomPick) {
        if (randomPick == attractorVector.size()) {
            randomPick -= 1;
        } else if (randomPick == 0) {
            randomPick += 1;
        } else {
            randomPick += 1;
        }
    }
    
    for(int i = 0; i < attractorVector.size(); i++) {
        if (i == randomPick) {
            attractorVector[i].active = false;
            lastRandomPick = i;
            cout << "current dispersing attractor: " + to_string(i) << endl;
        } else {
            attractorVector[i].active = true;
        }
    }
}
void AttractorSystem::displayAttractors() {
    for (int i = 0; i < attractorVector.size(); i++) {
        attractorVector[i].display(showAttractorEdge,showAttractorPoints,showAttractorFill);
    }
}


