#pragma once

#include "ofMain.h"

class Particles : public ofNode {
public:

    Particles();

    int boxsize;

    float mass;

    ofVec3f position;
    ofVec3f velocity;

    void setup();
    void update();
    void customDraw();

};
