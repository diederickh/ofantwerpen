#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    mov.initGrabber(320,240);
    blur.setup(320,240);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
    mov.update();
}

//--------------------------------------------------------------
void testApp::draw() {    
    
    blur.begin();
    blur.amount = ofMap(mouseX,0,ofGetWidth(),0,10,true);

    
    blur.iterations = ofMap(mouseY,0,ofGetHeight(),1,10,true);
    
    ofSetColor(255,0,0);
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, 50);
    
    blur.end();
    
    ofDrawBitmapString("amount: " + ofToString(blur.amount), 10,15);
    ofDrawBitmapString("iterations: " + ofToString(blur.iterations), 10,25);
}
