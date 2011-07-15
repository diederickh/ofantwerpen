/*
 *  Node.h
 *  iv
 *
 *  Created by Bert Balcaen on 13/07/11.
 *  Copyright 2011 Rekall Design. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"

class Node : public ofNode {
	public:
		ofColor color;
		float noiseZ;
		float noiseScale;
		int age;
		bool inImage;
		ofImage* image;
		void setup(ofImage* image);
		void update();
		void customDraw();
	
};
