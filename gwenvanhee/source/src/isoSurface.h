#pragma once

#include "ofMain.h"
#include "Particles.h"

class isoSurface : public ofNode {
public:

    isoSurface();

    int gridsize;
    int resolution;

    float isoValue;

    vector< vector<ofVec3f> > cubes;
    vector< vector<float> > isovalues;
    vector< vector<ofVec3f> > triangles;

    int edgeTable[256];
    int triTable[256][16];

    ofVec3f vertexInterpolation(ofVec3f point1, ofVec3f point2, float isovalue1, float isovalue2);

    void setup();
    void update(vector<Particles> &points);
    void customDraw();

};
