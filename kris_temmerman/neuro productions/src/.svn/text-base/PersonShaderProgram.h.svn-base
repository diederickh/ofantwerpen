//
//  PersonShaderProgram.h
//  ofxKinect
//
//  Created by Kris Temmerman on 24/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#ifndef PERSON_SHADER_PROG
#define PERSON_SHADER_PROG

#include "Constants.h"

#import "ShaderUtil.h"
#import "TextBase.h"
#import "Matrix3D.h"

class PersonShaderProgram 
{
    GLuint program;
	GLuint vShader;
	GLuint fShader;
	
    GLuint programB;
	GLuint vShaderB;
	GLuint fShaderB;
    
    
	float vpW;
    float vpH;
	Matrix3D *m ;
	
    GLint objectMatrixLocation;
    GLint worldMatrixLocation ;
    GLint perspMatrixLocation;
    
    GLfloat* perspectiveMatrix;
    
    float verh;  
    bool perspectiveisDirty;
    
public:
    PersonShaderProgram ();
    GLfloat* worldMatrix;   
    void renderPersons(float *data,int size);
    
    void windowResized(int w, int h);
    
};

#endif