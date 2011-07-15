#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(30);        
    img.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR);
    setMode(4);
}

//--------------------------------------------------------------
void testApp::draw() {
    img.draw(0,0);
}
    
void testApp::keyPressed(int key) {
    setMode(key-'0');
}

void testApp::setMode(int mode) {
    float w = ofGetWidth();
    float h = ofGetHeight();
    float cx = w/2;
    float cy = h/2;
    float hue,sat,bri,angle,dist;
    ofColor c;
    
    for (float y=0; y<h; y++) {
        for (float x=0; x<w; x++) {
            switch (mode) {
                case 1: //linear hue gradient
                    c = ofColor::fromHsb(x/w*255,255,255);
                    break;
                    
                case 2: //linear hsb gradient
                    hue = x/w*255;
                    sat = ofMap(y,0,h/2,0,255,true);
                    bri = ofMap(y,h/2,h,255,0,true);
                    c = ofColor::fromHsb(hue,sat,bri);
                    break;
                    
                case 3: //radial hue gradient
                    angle = atan2(y-w/2,x-h/2)+PI;
                    c = ofColor::fromHsb(angle/TWO_PI*255,255,255);
                    break;
                    
                case 4: //radial hsb gradient
                    angle = atan2(y-h/2,x-w/2)+PI;
                    dist = ofDist(x,y,w/2,h/2);
                    hue = angle/TWO_PI*255;
                    sat = ofMap(dist,0,w/4,0,255,true);
                    bri = ofMap(dist,w/4,w/2,255,0,true);
                    c = ofColor::fromHsb(hue,sat,bri);
                    break;
            }
            
            img.setColor(x,y,c);
        }
    }
    img.reloadTexture();    
}
