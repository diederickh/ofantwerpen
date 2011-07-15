/*
 *  BackGround.cpp
 *  polygonExample
 *
 *  Created by Kris Temmerman on 16/04/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#include "BackGround.h"


enum {
	ATTRIB_VERTEX_FLAT,
	ATTRIB_TEXTCORDS_FLAT
};


void BackGround::setup()
{
	ShaderUtil *su =new ShaderUtil;
	backVShader =su->getShader("shaders/FlatVertexShader.vsh",GL_VERTEX_SHADER );
	
	backFShader =su->getShader("shaders/FlatFragmentShader.fsh",GL_FRAGMENT_SHADER );
	backProgram = glCreateProgram();	
	free (su);
	
	glAttachShader(backProgram,backVShader);
	glAttachShader(backProgram,backFShader);
    
	glLinkProgram(backProgram);
	
	GLint linked;
	
	glGetProgramiv(backProgram,GL_LINK_STATUS, &linked);
	if (!linked)
	{
		
		GLint logLength;
		glGetProgramiv(backProgram, GL_INFO_LOG_LENGTH, &logLength);
		
		if (logLength > 0)
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetProgramInfoLog(backProgram, logLength, &logLength, log);
			cout <<"backProgram log: "<< log;
			free(log);
		}
		
		
		
	}
	
	glUseProgram(backProgram);
	
	glBindAttribLocation(backProgram, ATTRIB_VERTEX_FLAT, "position");
	glBindAttribLocation(backProgram, ATTRIB_TEXTCORDS_FLAT, "text_cords");

    
    this->projectionMatrixLocation =glGetUniformLocation(backProgram, "projectionMatrix");
	
    
    GLImageData *image =new GLImageData;
	textureID =image->setPath((string)"images/background.jpg");
    cout<< textureID << "imagetextureId";
	delete image;

}
void BackGround::windowResized(int wNew, int hNew)
{
    w =wNew;
    h =hNew;
    isDirty =true;
}
void BackGround::update()
{
    if(!isDirty)return;
    
    cout << " updtae background";
    backgroundData[0]=0;
	backgroundData[1]=0;
	backgroundData[2]=0;
	backgroundData[3]=0;
	
	backgroundData[4]=w;
	backgroundData[5]=0;
	backgroundData[6]=1;
	backgroundData[7]=0;
	
	backgroundData[8]=0;
	backgroundData[9]=h;
	backgroundData[10]=0;
	backgroundData[11]=1;
	
	
	
	backgroundData[12]=w;
	backgroundData[13]=h;
	backgroundData[14]=1;
	backgroundData[15]=1;
    
    

    
    projectionMatrix[0] =2.0/w;
    projectionMatrix[1] =0.0;
    projectionMatrix[2] =0.0;
    projectionMatrix[3] =-1;
    
    projectionMatrix[4] =0.0;
    projectionMatrix[5] =-2.0/h;
    projectionMatrix[6] =0.0;
    projectionMatrix[7] =1;
    
    projectionMatrix[8] =0.0;
    projectionMatrix[9] =0.0;
    projectionMatrix[10] =-1;
    projectionMatrix[11] =0.0;
    
    projectionMatrix[12] =0.0;
    projectionMatrix[13] =0.0;
    projectionMatrix[14] =0.0;
    projectionMatrix[15] =1;
    
    isDirty =false;

}
void BackGround::draw(){

    
   glUseProgram(backProgram);
  	glBindTexture(GL_TEXTURE_2D, textureID);
    
	
	glUniformMatrix4fv(this->projectionMatrixLocation,16, 0, projectionMatrix);
	
	
	GLfloat *vtxBuffer = backgroundData;
	
	glEnableVertexAttribArray(ATTRIB_VERTEX_FLAT);
	glEnableVertexAttribArray(ATTRIB_TEXTCORDS_FLAT);
	
	glVertexAttribPointer(ATTRIB_VERTEX_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	vtxBuffer+=2;
	glVertexAttribPointer(ATTRIB_TEXTCORDS_FLAT, 2, GL_FLOAT, 0, 4*sizeof(GLfloat), vtxBuffer);
	
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);



}