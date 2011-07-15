#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	ofBackground(0);
	ofSetVerticalSync(true);	
	ofDisableArbTex();

	img.loadImage("galaxy.png"); 
    img.bind();
    
    ofEnableAlphaBlending();
    ofSetColor(255,100);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);    
    glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::draw() {
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);    
    
    arcball.begin();

    for (int i=0; i<20; i+=2) {
        gluSphere(quadric, 150+i, 100, 100);
    }

    arcball.end();
}
