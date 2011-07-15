//
//  PersonShaderProgram.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 24/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "PersonShaderProgram.h"



enum {
	ATTRIB_VERTEX,
	
};
PersonShaderProgram::PersonShaderProgram ()
{
    /*
     
     
     prerenderer
     
     
     */
    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/PersonVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/PersonFragmentShader.fsh",GL_FRAGMENT_SHADER );
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
	
	glEnable(GL_POINT_SPRITE);
    
    glPointSize(23);
    
    
    
    
    this->worldMatrixLocation =glGetUniformLocation(program, "worldMatrix");
    this->perspMatrixLocation =glGetUniformLocation(program, "perspMatrix");
    verh =1;
    m  =new Matrix3D;
    m->perspProjMat (50, verh,1,600);
    perspectiveisDirty =false;
    
    
    perspectiveMatrix =  m->getRawData();
    glUniformMatrix4fv(this->perspMatrixLocation,16, 0, perspectiveMatrix);
    
    m->identity();
    
    
    
    
    /*
     
     
     full renderer
     
     
     */
    
    
    
    
    
    // m->rotate(-2,1,0,0);
   // worldMatrix =m->getRawData();
    
   // glUniformMatrix4fv(this->worldMatrixLocation,16, 0, worldMatrix);
    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
}
void PersonShaderProgram::renderPersons(float *data, int size)  
{
  //   glBlendFunc (GL_ONE,GL_SRC_ALPHA );
    if(size ==0 )return;
    glUseProgram(program);
    if(perspectiveisDirty)
    {
         glUniformMatrix4fv(this->worldMatrixLocation,16, 0, worldMatrix);
        glUniformMatrix4fv(this->perspMatrixLocation,16, 0, perspectiveMatrix);
        perspectiveisDirty =false ; 
      
    }

    
    
    
   
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0,0,data);
    
   // glDrawArrays(GL_POINTS,0,size/3 );
    // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 }


void PersonShaderProgram::windowResized(int w, int h){
    
    vpW =w;
    vpH =h;
    
    verh =(float)w/h;
    m->identity();
    m->perspProjMat (CAMERA_FOV, verh,1,900);
    
    
    
    perspectiveMatrix =  m->getRawData();
    perspectiveisDirty =true ; 
   
}

