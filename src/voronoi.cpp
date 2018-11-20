#include "voronoi.hpp"

Voronoi::Voronoi() {
    
    voronoiParameters.setName("Voronoi GUI panel");
    voronoiParameters.add(showVoronoi.set("Show voronoi", false));
    voronoiParameters.add(backgroundColorSet.set("Color voronoi background",false));
}

void Voronoi::initialize(glm::vec2 bounds){
    //  Add the cell seed to the container
    int nCells = 700;
    vector<glm::vec2> _points;
    for(int i = 0; i < nCells;i++){
        glm::vec2 newPoint = glm::vec2(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        _points.push_back(newPoint);
    }
    
    relaxedVoronoi.setBounds(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
    relaxedVoronoi.setPoints(_points);
    relaxedVoronoi.generate();
    
    voronoiCentroids = relaxedVoronoi.getPoints();
    
    int relaxIterations = 10;
    while(relaxIterations--){
        relaxedVoronoi.relax();
    }
    
    // VBO construction
    vector<ofxVoronoiCell> tempCells = relaxedVoronoi.getCells();
    for (int i = 0; i < tempCells.size() ; i++) {
        vector<glm::vec2> tempCell = tempCells[i].pts;
        
        vector<ofVec3f> tempCell3d;
        vector<ofIndexType> tempIndices;
        vector<float> tempColorChannels;
        vector<ofFloatColor> tempColors;
        
        for(int j = 0; j < tempCell.size(); j++){
            tempCell3d.push_back(ofVec3f(tempCell[j].x, tempCell[j].y, 0.0f));
            tempColorChannels.push_back(0);
            tempColorChannels.push_back(ofRandom(1.0));
            tempColorChannels.push_back(ofRandom(1.0));
            tempColors.push_back(ofFloatColor(tempColorChannels[j], // Red channel
                                              tempColorChannels[j+1], // Green channel
                                              tempColorChannels[j+2]  // Blue channel
                                              ));
            tempIndices.push_back(j);
        }
        
        vboVerts.push_back(tempCell3d);
        vboFaces.push_back(tempIndices);
        vboColor.push_back(tempColors);
    }
    
    for (int i = 0; i < vboVerts.size(); i++) {
        vboVector.push_back(*new ofVbo); // Free up slot for this VBO
        vboVector[i].setVertexData( &vboVerts[i][0], vboVerts[i].size(), GL_STATIC_DRAW );
        vboVector[i].setIndexData( &vboFaces[i][0], vboVerts[i].size(), GL_STATIC_DRAW );
        vboVector[i].setColorData( &vboColor[i][0], vboVerts[i].size(), GL_DYNAMIC_DRAW );
    }
}

void Voronoi::draw(){
    
    if (!showVoronoi) return;
    // VBO
    for (int i = 0; i < vboVector.size();i++) {
        glPointSize(10.f);
        vboVector[i].drawElements(GL_POLYGON, vboVerts[i].size()); // placeholder values
    }
    
    // particle system
    particleSystem.displayParticles();
    attractorSystem.displayAttractors();
    
    // Checking system
    if(particleSystem.particleDebug){
        for (int i = 0; i < voronoiCentroids.size(); i++) {
            for (int j = 0; j < particleSystem.particleVector.size(); j++) {
                glm::vec2 tempCentroid = voronoiCentroids[i];
                Particle tempParticle = particleSystem.particleVector[j];
                
                ofVec2f centroidLocation = ofVec2f(tempCentroid.x,tempCentroid.y);
                ofVec2f particleLocation = ofVec2f(tempParticle.location.x,tempParticle.location.y);
                
                float centroidDistance = centroidLocation.distance(particleLocation);
                
                if (centroidDistance < 50) {
                    int nearestVertex;
                    float vertexDistanceHolder = 100;
                    
                    for (int k = 0; k < vboVerts[i].size(); k++) {
                        ofVec2f vertexLocation = ofVec2f(vboVerts[i][k].x, vboVerts[i][k].y);
                        float vertexDistance = vertexLocation.distance(particleLocation);
                        
                        if (vertexDistance < 50) {
                            if(particleSystem.particleDebug){
                                ofDrawLine(particleLocation.x,particleLocation.y,
                                           vertexLocation.x,vertexLocation.y);
                            }
                            
                            ofFloatColor tempColor = vboColor[i][k];
                            float particleNoiseValue = ofClamp(ofNoise(i+ofGetFrameNum()*0.01,
                                                                       j+ofGetFrameNum()*0.0001)
                                                               ,0.5,1);
                            
                            // Values are rgb(255,51,255)converted to floatColor (Junction MAGENTA).
                            float stepSize = 0.02;
                            if (j % 2 == 0) {
                                if((tempColor[0] <= 1.0 - stepSize) * particleNoiseValue){
                                    tempColor[0] += stepSize;
                                } else if ((tempColor[0] > 1.0 + stepSize) * particleNoiseValue) {
                                    tempColor[0] -= stepSize;
                                }
                                
                                if ((tempColor[1] <= 0.2 - stepSize) * particleNoiseValue) {
                                    tempColor[1] += stepSize;
                                } else if ((tempColor[1] > 0.2 + stepSize) * particleNoiseValue) {
                                    tempColor[1] -= stepSize;
                                }
                                
                                if ((tempColor[2] <= 1.0 - stepSize) * particleNoiseValue) {
                                    tempColor[2] += stepSize;
                                } else if ((tempColor[2] > 1.0 + stepSize) * particleNoiseValue) {
                                    tempColor[2] -= stepSize;
                                }
                            } else {
                                if((tempColor[0] <= 0.207 - stepSize) * particleNoiseValue){
                                    tempColor[0] += stepSize;
                                } else if ((tempColor[0] > 0.207 + stepSize) * particleNoiseValue) {
                                    tempColor[0] -= stepSize;
                                }
                                
                                if ((tempColor[1] <= 0.886 - stepSize) * particleNoiseValue) {
                                    tempColor[1] += stepSize;
                                } else if ((tempColor[1] > 0.886 + stepSize) * particleNoiseValue) {
                                    tempColor[1] -= stepSize;
                                }
                                
                                if ((tempColor[2] <= 0.874 - stepSize) * particleNoiseValue) {
                                    tempColor[2] += stepSize;
                                } else if ((tempColor[2] > 0.874 + stepSize) * particleNoiseValue) {
                                    tempColor[2] -= stepSize;
                                }
                            }
                            
                            vboColor[i][k] = ofFloatColor(
                                                                      tempColor[0], // Red channel
                                                                      tempColor[1], // Green channel
                                                                      tempColor[2]  // Blue channel
                                                                      );
                        } // End of (vertexDistance < 50);
                    } // End of checking Vertexes to particle locations
                } // End of checking Centroids to particle locations
            }
        }
    }
    
    
    for(int i = 0; i < voronoiCentroids.size(); i++){
        for (int j = 0; j < vboVerts[i].size(); j++){
            ofFloatColor tempColor = vboColor[i][j];
            float noiseValue = ofClamp(ofNoise(i+ofGetFrameNum()*0.01,j+ofGetFrameNum()*0.0001),0.9,1);
            float fadeSpeed = 0.01;
            // Valyes are rgb(0,255,153) converted to floatColor (Junction GREEN);
            // Values are rgb(53,226,223) converted to floatColor (Junction TURQUOISE);
            if (backgroundColorSet) {
                if((tempColor[0] > 0.207 + fadeSpeed) * noiseValue){
                    tempColor[0] -= 0.01;
                } else if ((tempColor[0] <= 0.207 - fadeSpeed) * noiseValue) {
                    tempColor[0] += 0.01;
                }
                if((tempColor[1] > 0.886 + fadeSpeed) * noiseValue){
                    tempColor[1] -= 0.01;
                } else if ((tempColor[1] <= 0.886 - fadeSpeed)* noiseValue) {
                    tempColor[1] += 0.01;
                }
                if((tempColor[2] > 0.874 + fadeSpeed)* noiseValue){
                    tempColor[2] -= 0.01;
                } else if ((tempColor[2] <= 0.874 - fadeSpeed)* noiseValue) {
                    tempColor[2] += 0.01;
                }
            } else {
                if (tempColor[0] > 0.0) {
                    tempColor[0] -= 0.01;
                }
                if (tempColor[1] > 0.0) {
                    tempColor[1] -= 0.01;
                }
                if (tempColor[2] > 0.0) {
                    tempColor[2] -= 0.01;
                }
                
            }
            
            
            
            vboColor[i][j] = tempColor;
            vboVector[i].updateColorData(&vboColor[i][0], vboColor[i].size());
        
        }
    }
    
}

