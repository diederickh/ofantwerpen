/*
 *  BackGround.h
 *  polygonExample
 *
 *  Created by Kris Temmerman on 16/04/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#ifndef _BACKGROUND_H
#define _BACKGROUND_H



#include <iostream>

#import "ofImage.h"
#import "ShaderUtil.h"
#import "GLImageData.h"

using namespace std;

class BackGround {
	int w,  h;
	bool isDirty ;
    GLfloat projectionMatrix[16];
    
    GLuint backProgram;
	GLuint backVShader;
	GLuint backFShader;
	
	
	
	GLint projectionMatrixLocation;
	
	GLfloat backgroundData[16] ;	
	GLuint textureID; 
   
    
public:
	BackGround(): isDirty(true) { }

	void setup();
    void update();
	void windowResized(int w, int h);
	void draw();
	
};
#endif