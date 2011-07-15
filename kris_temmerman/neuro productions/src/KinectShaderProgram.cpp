//
//  KinectShaderProgram.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 13/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "KinectShaderProgram.h"

enum {
	ATTRIB_VERTEX, ATTRIB_NORMAL
	
};

KinectShaderProgram::KinectShaderProgram ()
{
    
    ShaderUtil *su =new ShaderUtil;
	vShader =su->getShader("shaders/KinectVertexShader.vsh",GL_VERTEX_SHADER );
	
	fShader =su->getShader("shaders/KinectFragmentShader.fsh",GL_FRAGMENT_SHADER );
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
    glBindAttribLocation(program, ATTRIB_NORMAL, "normal");
    
    worldMatrixLocation =glGetUniformLocation(program, "worldMatrix");
    perspMatrixLocation =glGetUniformLocation(program, "perspMatrix");
    objectMatrixLocation =glGetUniformLocation(program, "objMatrix");
    normalMatrixLocation =glGetUniformLocation(program, "normalMatrix");
      offsetLocation=glGetUniformLocation(program, "off");
    
 
   
    m  =new Matrix3D;
    
    m->perspProjMat(30, 1, 1, 1000);
    
    perspectiveMatrix =  m->getRawData();
   
    
       
    
        

    Matrix3D *m2 =new Matrix3D;
    m2->identity();
   // m2->translate(0,0,-01);
    m2->rotate(20,0,1,0);
    worldMatrix =m2->getRawData();
 
 
    
    
    
    
    
  
  
 
    
}

void KinectShaderProgram::enable  ()
{
   
    glUseProgram(program);
   // glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
   
    
}

void KinectShaderProgram::renderData(float *data,int size)
{
    //if(ofGetFrameNum()<20)return;
    cout<<mouseX <<"\n";
    //GLfloat *vtxBuffer =data ;
    float rot = ofGetFrameNum()*2;
    Matrix3D *m2 =new Matrix3D;
    m2->identity();
   m2->translate(0,0,-500);
    Matrix3D *m3 =new Matrix3D;
    Matrix3D *m4 =new Matrix3D; 
    
    Matrix3D *m5 =new Matrix3D;
    Matrix3D *m6 =new Matrix3D; 
   // cout<<mouseX<<"mx";
    if(ofGetFrameNum()%2==1)
    {
       m3->rotate(rot+180,0,1,0);
        m2->translate(0,0,mouseX);
      //  m5->translate(0,0,-100);
        //m6->rotate(rot+180,0,1,0);
    }
   else
    {
         m2->translate(0,0,mouseX);
        m3->rotate(rot,0,1,0);
    }
   // m2->rotate(ofGetFrameNum()/2,0,1,0);
    //m2->translate(0,0,-10000);
    m4->multiply(m3->getRawData(),m2->getRawData());
    
    m5->translate(0,0,-800);
    
    worldMatrix =m5->getRawData();
    objectMatrix =m4->getRawData();
    normalMatrix =m3->getRawData();
    glUniformMatrix4fv(perspMatrixLocation,16, 0, perspectiveMatrix);
    glUniformMatrix4fv(worldMatrixLocation,16, 0, worldMatrix);
   glUniformMatrix4fv(objectMatrixLocation,16, 0, objectMatrix);
    glUniformMatrix4fv(normalMatrixLocation,16, 0, normalMatrix);
   // glUniform1f(offsetLocation,mouseX);
    
    glEnableVertexAttribArray(ATTRIB_VERTEX);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
    
	//cout<<  vertices[3]<< " "<<vertices[4] <<" " <<vertices[5]<<"__";
	
	glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 6*sizeof(GLfloat), vertices);
	vertices+=3;
	glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, 0, 6*sizeof(GLfloat), vertices);	
	
	glDrawElements(GL_TRIANGLES,numIndices*3, GL_UNSIGNED_INT, indices );
   // glDrawArrays(GL_LINES, 0, 100);
    GLenum errCode;
    errCode = glGetError();
    if (errCode != GL_NO_ERROR) 
    {
        if (errCode == GL_INVALID_ENUM)cout << "invalid enumeration" ;
        if (errCode == GL_INVALID_VALUE)cout << "invalid value" ;
        if (errCode == GL_INVALID_OPERATION)cout << "invalid operation" ;
        if (errCode == GL_OUT_OF_MEMORY)cout << "invalid out of memory" ;
        
    }	
    
    
    //glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 3*sizeof(GLfloat), data);
  // glDrawElements(<#GLenum mode#>, <#GLsizei count#>, <#GLenum type#>, <#const GLvoid *indices#>)
    //glDrawArrays(GL_TRIANGLES, 0, size);
    
    //cout << size<< "\n";
}




void KinectShaderProgram::disable  ()
{
    //glDisable(GL_DEPTH_TEST);
    
    
}
