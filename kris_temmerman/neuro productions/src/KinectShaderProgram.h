//
//  KinectShaderProgram.h
//  ofxKinect
//
//  Created by Kris Temmerman on 13/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#ifndef _KINECTSHADER_PROG
#define _KINECTSHADER_PROG

#import "ShaderUtil.h"
#import "SpriteBase.h"
#import "Matrix3D.h"
#include "Constants.h"
class KinectShaderProgram 
{
    GLuint program;
	GLuint vShader;
	GLuint fShader;
	
	
	Matrix3D *m ;
	
    
    GLint worldMatrixLocation ;
    GLint offsetLocation ;
    GLint perspMatrixLocation;
    GLint objectMatrixLocation  ;
    GLint normalMatrixLocation  ;
    GLfloat* perspectiveMatrix;
    
    GLfloat* worldMatrix; 
    GLfloat* objectMatrix;
    GLfloat* normalMatrix;
    
    float verh;  
    bool perspectiveisDirty;
    
public:
    KinectShaderProgram  ();
    
    void enable();
    void renderData(float *data,int size);
 
    void disable();
    int numIndices;
    unsigned int  *indices;
    float *vertices;
    
    float mouseX;
};

#endif