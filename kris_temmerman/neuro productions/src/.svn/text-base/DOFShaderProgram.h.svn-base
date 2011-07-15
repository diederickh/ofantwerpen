//
//  DOFShaderProgram.h
//  renderTest
//
//  Created by Kris Temmerman on 21/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#ifndef _DOFSHADER_PROG
#define _DOFSHADER_PROG


#import "ShaderUtil.h"
#import "SpriteBase.h"
class DOFShaderProgram 
{
    GLuint program;
	GLuint vShader;
	GLuint fShader;
	
	
	
	GLint projectionMatrixLocation;
   GLint kernalSizeLocation;
    GLint offsetLocation;
    GLint scaleLocation;
    
    
public:
    DOFShaderProgram();
    
    void enable();
    void renderSprite(SpriteBase *spriteBase);
    void disable();
    
};

#endif