#include "Particles.h"

// constructor
Particles::Particles() {
}

void Particles::setup() {
    position    = ofVec3f(boxsize*.5, boxsize*.5, boxsize*.5);
    velocity    = ofVec3f(ofRandom(-30,30), ofRandom(-30,30), ofRandom(-30,30) );
    mass        = 10;//ofRandom(0,15);
}

void Particles::update() {

    position += velocity/mass;
    setPosition(position);

    // check boundaries
    if(position.x<0 || position.x>boxsize) velocity.x*=-1;
    if(position.y<0 || position.y>boxsize) velocity.y*=-1;
    if(position.z<0 || position.z>boxsize) velocity.z*=-1;
}


void Particles::customDraw() {
    ofFill();
    ofSetColor(255,0,255);
    ofSphere(0,0,mass);
}
