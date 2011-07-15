//
//  StrokeShaderProgram.h
//  ofxKinect
//
//  Created by Kris Temmerman on 12/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#ifndef _STROKESHADER_PROG
#define _STROKESHADER_PROG

#include "Constants.h"
#import "ShaderUtil.h"
#import "SpriteBase.h"
#import "Matrix3D.h"
#import "Blob.h"

class StrokeShaderProgram 
{
    GLuint program;
	GLuint vShader;
	GLuint fShader;
	
	
	Matrix3D *m ;
	
  
    GLint worldMatrixLocation ;
    GLint perspMatrixLocation;
    GLint colorLocation;
    GLfloat* perspectiveMatrix;
    
    float verh;  
    bool perspectiveisDirty;
    
public:
    StrokeShaderProgram ();
    GLfloat* worldMatrix; 
    void enable();
    void renderStroke(Blob *blob);
    //void renderSprite(SpriteBase *spriteBase);
    void disable();
    void windowResized(int w, int h);
    
};

#endif