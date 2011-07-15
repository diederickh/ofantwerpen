#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void draw();
    
    ofVbo cube;
    ofEasyCam cam;
};
