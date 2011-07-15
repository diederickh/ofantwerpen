#pragma once

#include "ofMain.h"
#include "ofxArcBall.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void draw();
        
    ofxArcBall arcball;
    ofImage img;
    GLUquadricObj *quadric;
};
