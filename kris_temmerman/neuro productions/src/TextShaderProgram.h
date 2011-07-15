//
//  TextShaderProgram.h
//  ofxKinect
//
//  Created by Kris Temmerman on 16/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#ifndef _TextSHADER_PROG
#define _TextSHADER_PROG

#import "ShaderUtil.h"
#import "TextBase.h"
#import "Matrix3D.h"

class TextShaderProgram 
{
    GLuint program;
	GLuint vShader;
	GLuint fShader;
	
	
	Matrix3D *m ;
	
    GLint objectMatrixLocation;
    GLint worldMatrixLocation ;
    GLint perspMatrixLocation;
    
    GLfloat* perspectiveMatrix;
    GLfloat* worldMatrix; 
    float verh;  
    bool perspectiveisDirty;
    
public:
    TextShaderProgram ();
    
    void enable();
    void renderSprite(TextBase *spriteBase);
    void disable();
    void windowResized(int w, int h);
    
};

#endif