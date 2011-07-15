//
//  StrokeShaderProgram.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 12/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "StrokeShaderProgram.h"
enum {
	ATTRIB_VERTEX
	
};
StrokeShaderProgram::StrokeShaderProgram ()
{
    
    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/StrokeVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/StrokeFragmentShader.fsh",GL_FRAGMENT_SHADER );
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
	
	glBindAttribLocation(program, ATTRIB_VERTEX, "position");
	
	
    
    
    
    
    this->colorLocation =glGetUniformLocation(program, "color");
   
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
    
   // glUniformMatrix4fv(this->worldMatrixLocation,16, 0, worldMatrix);
    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    
}

void StrokeShaderProgram::enable  ()
{
   glEnable(GL_MULTISAMPLE);
   glUseProgram(program);
   
    if(perspectiveisDirty)
    {
         glUniformMatrix4fv(this->worldMatrixLocation,16, 0, worldMatrix);
        glUniformMatrix4fv(this->perspMatrixLocation,16, 0, perspectiveMatrix);
        
    }
    
    
}

void StrokeShaderProgram::renderStroke(Blob *blob)
{
    
   /*cout <<"\n blob in shader draw " <<" " << blob->numIndices<<"\n data :";
    for(int k=0;k<blob->numIndices;k++)
    {
        cout << blob->data[k]<<" ";
        
        
    }*/
    
    
    GLfloat value[4] ;
  /* value[0] =blob->r;
    value[1] =blob->g;
    value[2] =blob->b;
    value[3] =1.0;
    glUniform4fv(colorLocation, 4, value);*/  
    
    GLfloat *vtxBuffer =blob->data;
	
	glEnableVertexAttribArray(ATTRIB_VERTEX);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 3*sizeof(GLfloat), vtxBuffer);
//glDrawArrays(GL_LINE_LOOP, 0, blob->numIndices);
//glDrawArrays(GL_POLYGON, 0, blob->numIndices);
    
    value[0] =1;
    value[1] =1;
    value[2] =1;
    value[3] =1;
    glUniform4fv(colorLocation, 4, value);
    glDrawArrays(GL_LINE_LOOP, 0, blob->numIndices);
  
}



void StrokeShaderProgram::disable  ()
{
    glDisable(GL_MULTISAMPLE);
    //glDisable(GL_DEPTH_TEST);
    
    
}
void StrokeShaderProgram::windowResized(int w, int h){
    verh =(float)w/h;
    m->identity();
    m->perspProjMat (CAMERA_FOV, verh,1,900);
    
    
    
    perspectiveMatrix =  m->getRawData();
    perspectiveisDirty =true ; 
    
}