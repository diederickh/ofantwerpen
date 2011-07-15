#pragma once

#include "ofMain.h"
#include "ofxBlurShader.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber mov;
    ofxBlurShader blur;
};
