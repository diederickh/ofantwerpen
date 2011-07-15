#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::update(){
    
	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
	//ofSetColor(0x000000);
    ofNoFill();
    
	for (int i = 0; i < particles.size(); i++){
        if (particles[i].alpha > 10) {
            particles[i].alpha--;
            
        } /*else {
            particles.erase(particles.begin());
        }*/
       
        ofSetColor(0,250,210,particles[i].alpha);
        ofSetLineWidth(3);
		particles[i].draw();
        
        ofSetLineWidth(1);
        ofSetColor(100, 100, 100,particles[i].alpha);
        ofLine(particles[i].pos.x, particles[i].pos.y, particles[i-1].pos.x, particles[i-1].pos.y);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
	float dx = x - prevMouseX;
	float dy = y - prevMouseY;

    for(int i = 0; i<10;++i){
        particle myParticle;
        myParticle.alpha = 255;
        //dx = ofRandom(0,5)*dx*-0.2;
        //dy = ofRandom(0,5)*dy*-0.2;
        dx = dx*-0.2;
        dy = dy*-0.2;
        myParticle.setInitialCondition(x,y,dx,dy);
        particles.push_back(myParticle);
	}
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	particles.clear();
}