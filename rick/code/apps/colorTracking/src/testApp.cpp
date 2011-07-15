#include "testApp.h"

int w = 320;
int h = 240;

//--------------------------------------------------------------
void testApp::setup(){
    mov.initGrabber(w,h);
    
    rgb.allocate(w,h);
    grey.allocate(w,h);
    hsb.allocate(w,h);
    hue.allocate(w,h);
    sat.allocate(w,h);
    bri.allocate(w,h);
    filtered.allocate(w,h);
    
}

//--------------------------------------------------------------
void testApp::update(){
    mov.update();

    if (mov.isFrameNew()) {
        rgb.setFromPixels(mov.getPixels(), w,h);
        rgb.mirror(false,true);
        
        grey = rgb;
        grey.threshold(100);
        
        hsb = rgb;
        hsb.convertRgbToHsv();
        
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered.getPixels()[i] = 
                ofInRange(hue.getPixels()[i],findHue-5,findHue+5) ? 255 : 0;
        }
        
        filtered.flagImageChanged();
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    mov.draw(0,0);
    rgb.draw(w,0);
    grey.draw(2*w,0);
    hsb.draw(0,h);
    hue.draw(w,h);
    filtered.draw(2*w,h);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    int mx = x%w;
    int my = y%h;
    findHue = hue.getPixels()[my*w+mx];
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
