#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);
    glEnable(GL_DEPTH_TEST);

    ofMesh cubeMesh;
        
    char c[] = "011111101001111110100101110010000100"
               "010011001000010110111011000100101001";
    
    for (int i=0,x,y,z; i<72; i+=3) {
        
        x = c[i+0]-'0';
        y = c[i+1]-'0'; 
        z = c[i+2]-'0'; 
        
        cubeMesh.addColor(ofFloatColor(x,y,z));
        cubeMesh.addVertex(ofVec3f(x*2-1,y*2-1,z*2-1));
    }
    
    cube.setMesh(cubeMesh, GL_STATIC_DRAW);
 }

//--------------------------------------------------------------
void testApp::draw(){
    cam.begin();
    ofScale(100,100,100);
    cube.draw(GL_QUADS,0,24);
}

//cylinder    
//float step = TWO_PI/6;
//
//for (float i=0; i<=TWO_PI; i+=step) {
//    
//    cylinderMesh.addColor(ofColor::fromHsb(i/TWO_PI*255,255,255));
//    cylinderMesh.addVertex(ofVec3f(sin(i),cos(i),255));
//    
//    cylinderMesh.addColor(ofColor::fromHsb((i+step)/TWO_PI*255,255,255));
//    cylinderMesh.addVertex(ofVec3f(sin(i+step),cos(i+step),255));
//    
//    cylinderMesh.addColor(ofFloatColor(1,1,1));
//    cylinderMesh.addVertex(ofVec3f(0,0,255));
//}
//
//cylinder.setMesh(cylinderMesh, GL_STATIC_DRAW);
