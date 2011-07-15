//
//  DOFShaderProgram.cpp
//  renderTest
//
//  Created by Kris Temmerman on 21/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "DOFShaderProgram.h"
enum {
	ATTRIB_VERTEX_FLAT,
	ATTRIB_TEXTCORDS_FLAT
};



DOFShaderProgram::DOFShaderProgram ()
{
    
    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/DOFVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/DOFFragmentShader.fsh",GL_FRAGMENT_SHADER );
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
	
    
	glBindAttribLocation(program, ATTRIB_VERTEX_FLAT, "position");
	glBindAttribLocation(program, ATTRIB_TEXTCORDS_FLAT, "text_cords");

    
    projectionMatrixLocation =glGetUniformLocation(program, "projectionMatrix");
   kernalSizeLocation=glGetUniformLocation(program, "kernalSize");
   offsetLocation=glGetUniformLocation(program, "offset");
   scaleLocation=glGetUniformLocation(program, "scale");
 
}

void DOFShaderProgram::enable()
{
    glUseProgram(program);
    
    
    
}
void DOFShaderProgram::renderSprite  (SpriteBase *spriteBase)
{
    if(!spriteBase->isDirtyDOF) return;
    ///cout <<"r";
    
  
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, spriteBase->fboIdDOF);
    glClear(GL_COLOR_BUFFER_BIT );
    glViewport(0,0,spriteBase->width+60, spriteBase->height+60);
    
    
    glBindTexture(GL_TEXTURE_2D,spriteBase->lineTextureId);
	
    
    glUniformMatrix4fv( projectionMatrixLocation,16, 0, spriteBase->projectionMatrix);
    
   
    
    
 
    int size = spriteBase->kernalSize;
    
    glUniform1i(kernalSizeLocation,size);
    
    glUniform2fv(offsetLocation, size*2, spriteBase->offsetWidth);
    glUniform1fv(scaleLocation, size, spriteBase->dofKernel);
    

    
	
    
    
	glEnableVertexAttribArray(ATTRIB_VERTEX_FLAT);
	glEnableVertexAttribArray(ATTRIB_TEXTCORDS_FLAT);	
	
	GLfloat *vtxBuffer = spriteBase->planeDataL;
	
	
	
	glVertexAttribPointer(ATTRIB_VERTEX_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	vtxBuffer+=2;
	glVertexAttribPointer(ATTRIB_TEXTCORDS_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    /// pass2
    
    
    
  
    



    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, spriteBase->fboIdDOF2);
   
    
    glClear(GL_COLOR_BUFFER_BIT );
   
      
    glBindTexture(GL_TEXTURE_2D,spriteBase->dofTextureId);
    glUniform2fv(offsetLocation, size*2,  spriteBase->offsetHeight);
    
    vtxBuffer = spriteBase->planeData;
	
	glEnableVertexAttribArray(ATTRIB_VERTEX_FLAT);
	glEnableVertexAttribArray(ATTRIB_TEXTCORDS_FLAT);
	
	glVertexAttribPointer(ATTRIB_VERTEX_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	vtxBuffer+=2;
	glVertexAttribPointer(ATTRIB_TEXTCORDS_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
   
    
    //
    spriteBase->isDirtyDOF =false;
    
	
	
}

void DOFShaderProgram::disable()
{
    // unbind FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    
    
}