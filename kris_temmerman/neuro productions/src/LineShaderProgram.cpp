//
//  LineShaderProgram.cpp
//  polygonExample
//
//  Created by Kris Temmerman on 20/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "LineShaderProgram.h"

enum {
	ATTRIB_LINE_FLAT,
	
};


LineShaderProgram::LineShaderProgram ()
{

    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/LineVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/LineFragmentShader.fsh",GL_FRAGMENT_SHADER );
	program = glCreateProgram();	
	free (su);
	
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
    
	glLinkProgram(program);
	
	GLint linked;
	
	glGetProgramiv(program,GL_LINK_STATUS, &linked);
	if (!linked)
	{
		
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		
		if (logLength > 0)
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetProgramInfoLog(program, logLength, &logLength, log);
			cout <<"backProgram log: "<< log;
			free(log);
		}
		
		
		
	}
	
	glUseProgram(program);
	
    glBindAttribLocation(program, ATTRIB_LINE_FLAT, "position");
    
    projectionMatrixLocation =glGetUniformLocation(program, "projectionMatrix");
alphaLocation =glGetUniformLocation(program, "alpha");

}

void LineShaderProgram::enable()
{
    glClearColor(0, 0, 0, 0);
    glLineWidth(1.0);
  glUseProgram(program);
       
 // glEnable(GL_LINE_SMOOTH);

}
void LineShaderProgram::renderSprite  (SpriteBase *spriteBase)
{
    if(!spriteBase->isDirtyLines) return;
    ///cout <<"r";
    glViewport(0,0,spriteBase->width, spriteBase->height);
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, spriteBase->fboIdLine);
	glUniformMatrix4fv( projectionMatrixLocation,16, 0, spriteBase->projectionMatrixLines);

	// clear buffers
    
	glClear(GL_COLOR_BUFFER_BIT );
	glVertexAttribPointer(ATTRIB_LINE_FLAT, 2, GL_FLOAT, 0, 0, spriteBase->lineData);
    glUniform1f(alphaLocation,0.90f);

    glDrawArrays(GL_POLYGON,0,10);
    glVertexAttribPointer(ATTRIB_LINE_FLAT, 2, GL_FLOAT, 0, 0, spriteBase->lineData);
   
 glUniform1f(alphaLocation,1.0f);
    glDrawArrays(GL_LINE_LOOP,0,10);
   
    
    
	spriteBase->isDirtyLines =false;
    
   	
}

void LineShaderProgram::disable()
{
    // unbind FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    

}