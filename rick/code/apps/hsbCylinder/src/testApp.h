#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void draw();
    
    ofEasyCam camera;
    float step,steps;

    ofMesh mesh;
};
