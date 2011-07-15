#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(30);
    
    int w = ofGetWidth();
    int h = ofGetHeight();

    img.allocate(w,h,OF_IMAGE_COLOR);

    for (float y=0; y<h; y++) {
        for (float x=0; x<w; x++) {
            
            float hue = x/w*255;
            float sat = ofMap(y,0,h/2,0,255,true);
            float bri = ofMap(y,h/2,h,255,0,true);
            
            img.setColor(x,y,ofColor::fromHsb(hue,sat,bri));
        }
    }

    img.reloadTexture();    

}

//--------------------------------------------------------------
void testApp::draw() {

    img.draw(0,0);
}
