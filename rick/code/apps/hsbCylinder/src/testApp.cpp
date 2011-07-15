#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);
    ofSetFrameRate(30);
    glEnable(GL_DEPTH_TEST);
    
    steps = 120;
    step = TWO_PI/steps;

    //triangles
    for (int j=0; j<2; j++) {
        
        //create vertices and set colors
        mesh.addColor(j*255);
        mesh.addVertex(ofVec3f(0,0,j));
        
        for (float i=0; i<steps; i++) {
            mesh.addColor(ofColor::fromHsb(i/steps*255,255,j*255));
            mesh.addVertex(ofVec3f(sin(i/steps*TWO_PI),cos(i/steps*TWO_PI),j));
        }
        
        //top & bottom
        for (int k=0,a,b,c; k<steps; k++) {
            a = j*steps+j;
            b = j*steps+j+k+1;
            c = j*steps+j+k+2;
            if (c>a+steps) c -= steps;
            
            mesh.addTriangle(a,b,c);
        }        
    }

    //side
    for (float i=1,a,b; i<=steps; i++) {
        mesh.addTriangle(i,i+1,i+steps+2);
        mesh.addTriangle(i,i+steps+1,i+steps+2); 
    }
 }

//--------------------------------------------------------------
void testApp::draw(){
    camera.begin();
    ofScale(125,125,125);
    mesh.drawFaces();
}
