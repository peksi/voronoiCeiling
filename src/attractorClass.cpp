//
//  attractorClass.cpp
//  junctionCeiling_1
//
//  Created by Robbert Groenendijk on 30/10/2018.
//

#include "attractorClass.hpp"

Attractor::Attractor() {
    cout << "Spawned new attractor" << endl;
    
    attractorShape.setMode(ofPath::POLYLINES);
    attractorShape.setFillColor(ofColor(0));
    
    cornerCount = 0;
    editState = true;
    fullySet = false;
    attractorMass = ofRandom(0,0.5);
}
void Attractor::activateCornerPoint(int _pointIndex,bool _state) {
    cornerState[_pointIndex] = _state;
}
void Attractor::changeCornerPoint(int _pointIndex) {
    cornerPoints[_pointIndex] = ofVec2f(ofGetMouseX(),ofGetMouseY());
}
void Attractor::setCornerPoints() {
    if (cornerCount >= 4) {
        cout << "attractor fully set, spawn a new one" << endl;
        fullySet = true;
        editState = false;
        return;
    } else {
        cornerPoints.push_back(*new ofVec2f(ofGetMouseX(),ofGetMouseY()));
        cornerState.push_back(false);
        cornerCount += 1;
        
        if (cornerCount >= 4) {
            cout << "attractor fully set, spawn a new one" << endl;
            fullySet = true;
            editState = false;
        }
        
        attractorPoly.addVertex(ofPoint(ofGetMouseX(),ofGetMouseY()));
        attractorPoly.setClosed(true);
        attractorCentroid = attractorPoly.getCentroid2D();
        
        // Move polyline indices to ofPath for solid color shape.
        attractorShape.moveTo(attractorPoly[0]);
        for( int i = 1; i < attractorPoly.size(); ++i ) {
            attractorShape.lineTo(attractorPoly[i]);
        }
        
    }
}
void Attractor::updateShape() {
    attractorPoly.clear();
    for (int i = 0; i < cornerPoints.size(); i++) {
        attractorPoly.addVertex(ofPoint(cornerPoints[i].x,cornerPoints[i].y));
        attractorPoly.setClosed(true); // Mesh was reset so recall setClosed.
        attractorCentroid = attractorPoly.getCentroid2D();
        
        // Move polyline indices to ofPath for solid color shape.
        attractorShape.clear();
        attractorShape.moveTo(attractorPoly[0]);
        for( int i = 1; i < attractorPoly.size(); ++i ) {
            attractorShape.lineTo(attractorPoly[i]);
        }
    }
}
void Attractor::display(bool _showEdge, bool _showPoints, bool _showFill) {
    for (int i = 0; i < cornerPoints.size(); i++) {
        if (cornerState[i] == true) {
            ofSetColor(0, 255, 0,50);
        } else {
            ofSetColor(0, 0, 255,50);
        }
        if (_showPoints == true) {
            ofDrawCircle(cornerPoints[i].x, cornerPoints[i].y, 5);
        }
        
    }
    if (_showFill == true) {
        attractorShape.draw(); // Draws fill
    }
    if (_showEdge == true) {
        attractorPoly.draw(); // Draws outline
    }
}
