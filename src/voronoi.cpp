#include "voronoi.h"

vector<glm::vec3> cellCentroids;
vector<float>   cellRadius;
vector<ofVboMesh>  cellMeshes;
vector<ofVboMesh>  cellMeshWireframes;

VoronoiTissue::VoronoiTissue() {
    
}

void VoronoiTissue::makeTissue(int _nCells, int _width, int _height, int _deep){
    
    //  Fresh begining
    //
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();
    
    //  Define a container
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
    con.add_wall(cyl);
    
    //  Add the cell seed to the container
    for(int i = 0; i < _nCells;i++){
        glm::vec3 newCell = ofVec3f(ofRandom(-_width*0.5,_width*0.5),
                                    ofRandom(-_height*0.5,_height*0.5),
                                    0);
        
        
        addCellSeed(con, newCell, i, true);
    }
    
    cellMeshes = getCellsFromContainer(con,0.0);
    cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    cellRadius = getCellsRadius(con);
    cellCentroids = getCellsCentroids(con);
}

void VoronoiTissue::drawTissue(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0); // center the voronoi
    glEnable(GL_DEPTH_TEST);
    
    for(int i = 0; i < cellMeshes.size(); i++){
        ofSetColor(ofColor(100, 100, 140));
        cellMeshes[i].drawFaces();
        
        ofPushStyle();
        ofSetLineWidth(3);
        ofSetColor(255);
        cellMeshWireframes[i].draw();
        ofPopStyle();
    }
    
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
    
}
