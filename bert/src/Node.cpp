/*
 *  Node.cpp
 *  iv
 *
 *  Created by Bert Balcaen on 13/07/11.
 *  Copyright 2011 Rekall Design. All rights reserved.
 *
 */

#include "Node.h"

void Node::setup(ofImage* _image){
	image = _image;
	inImage = true;
	age = 0;
}

void Node::update(){

	ofVec3f position = getPosition();
	
	inImage = position.x > 0 && position.x < (*image).width -1 && position.y > 0 && position.y < (*image).height - 1;
	
	if (inImage) {
		
		age ++;

		ofColor imageColor = (*image).getColor(position.x, position.y);
		float speed = ofMap(imageColor.getBrightness(), 0, 255, 0.1, 10);
		float noiseVal = ofNoise(position.x * noiseScale, position.y * noiseScale, noiseZ);

		float angle = noiseVal * PI * 2 * ofMap(imageColor.getBrightness(), 0, 255, 0, 4);
		position.x += speed * sin(angle);
		position.y += speed * cos(angle);
		setPosition(position);
		
		color.set(ofMap(imageColor.getBrightness(), 0, 255, 0, 255));

	}
	
}

void Node::customDraw(){
	if (inImage) {
		ofSetColor(color);
		ofRect(0, 0, 1, 1);
	}
}

