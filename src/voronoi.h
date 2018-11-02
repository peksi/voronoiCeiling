#include "ofMain.h"
#include "ofxVoro.h"

class VoronoiTissue {
public:
    vector<glm::vec3> cellCentroids;
    vector<float>   cellRadius;
    vector<ofVboMesh>  cellMeshes;
    vector<ofVboMesh>  cellMeshWireframes;
    void makeTissue(int _nCells, int _width, int _height, int _deep);
    void draw();

    
    VoronoiTissue();
    
};
