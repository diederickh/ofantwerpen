//
//  SpriteBase.h
//  polygonExample
//
//  Created by Kris Temmerman on 20/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#ifndef _SPRITEBASE
#define _SPRITEBASE

#import <GLUT/GLUT.h>
#import "GausianBlurFactory.h"
#import "Matrix3D.h"


#include <iostream>

class SpriteBase {
	
   
   
    
    float speed;
    
    int blurRadius;
   
    
public:
    float width;
    float height;
    float z;
    float x;
    float y;
    
    float targetZ;
    float targetY;
    
    
    float *dofKernel;
    float *offsetWidth;
    float *offsetHeight;
    int kernalSize;
    
    bool isDirtyLines;
    bool isDirtyDOF;
    
    GLfloat*  projectionMatrixLines;
    GLfloat*  projectionMatrix;
    GLfloat* objectMatrix;  
    
   	GLuint fboIdLine;
    GLuint fboIdDOF;
    GLuint fboIdDOF2;
    
    
    GLuint lineTextureId;
    GLuint dofTextureId;
    GLuint dofTextureId2;
    
    GLuint textureId;
   
    GLfloat planeData[16] ;	
    GLfloat planeDataSmall[16] ;	
    GLfloat planeDataL[16] ;	
    GLfloat lineData[10];
    
    SpriteBase(): isDirtyLines(true) ,isDirtyDOF(true) { };
    
   
    
    void setup();
    void update();
    
    void setZ(float zPos);
      
    
   
	
	
    
};

#endif