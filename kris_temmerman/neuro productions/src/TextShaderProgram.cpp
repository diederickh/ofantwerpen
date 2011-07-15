//
//  TextShaderProgram.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 16/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "TextShaderProgram.h"


enum {
	ATTRIB_VERTEX_FLAT,
	ATTRIB_TEXTCORDS_FLAT
};
TextShaderProgram::TextShaderProgram ()
{
    
    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/TextVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/TextFragmentShader.fsh",GL_FRAGMENT_SHADER );
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
	
    
    
    
    
    
    this->objectMatrixLocation =glGetUniformLocation(program, "objectMatrix");
    this->worldMatrixLocation =glGetUniformLocation(program, "worldMatrix");
    this->perspMatrixLocation =glGetUniformLocation(program, "perspMatrix");
    verh =1;
    m  =new Matrix3D;
    m->perspProjMat (50, verh,1,600);
    perspectiveisDirty =false;
    
    
    perspectiveMatrix =  m->getRawData();
    glUniformMatrix4fv(this->perspMatrixLocation,16, 0, perspectiveMatrix);
    
    m->identity();
    
    // m->rotate(-2,1,0,0);
    worldMatrix =m->getRawData();
    
    glUniformMatrix4fv(this->worldMatrixLocation,16, 0, worldMatrix);
    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
}

void TextShaderProgram::enable  ()
{
    glUseProgram(program);
    if(perspectiveisDirty)
    {
        
        glUniformMatrix4fv(this->perspMatrixLocation,16, 0, perspectiveMatrix);
        
    }
    
    
}
void TextShaderProgram::renderSprite  (TextBase *spriteBase)
{
    glBindTexture(GL_TEXTURE_2D, spriteBase->dofTextureId2);
    glUniformMatrix4fv(this->objectMatrixLocation,16, 0, spriteBase->objectMatrix);
	
    GLfloat *vtxBuffer = spriteBase->planeDataSmall;
	
	glEnableVertexAttribArray(ATTRIB_VERTEX_FLAT);
	glEnableVertexAttribArray(ATTRIB_TEXTCORDS_FLAT);
	
	glVertexAttribPointer(ATTRIB_VERTEX_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	vtxBuffer+=2;
	glVertexAttribPointer(ATTRIB_TEXTCORDS_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    
}

void TextShaderProgram::disable  ()
{
    //glDisable(GL_DEPTH_TEST);
    
    
}
void TextShaderProgram::windowResized(int w, int h){
    verh =(float)w/h;
    m->identity();
    m->perspProjMat (50, verh,1,900);
    
    
    
    perspectiveMatrix =  m->getRawData();
    perspectiveisDirty =true ; 
    ; 
}