//
//  TextBase.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 16/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "TextBase.h"

void TextBase::setup(){
    
    GLfloat w = 190.0 ;
    GLfloat h =50.0;
    
    width =w;
    height =h;
    
    
    /*planeData[0]=0;
     planeData[1]=0;
     planeData[2]=0;
     planeData[3]=0;
     
     planeData[4]=w;
     planeData[5]=0;
     planeData[6]=1;
     planeData[7]=0;
     
     planeData[8]=0;
     planeData[9]=h;
     planeData[10]=0;
     planeData[11]=1;
     
     
     
     planeData[12]=w;
     planeData[13]=h;
     planeData[14]=1;
     planeData[15]=1;*/
    
    
    
    
    planeDataL[0]=0+30;
	planeDataL[1]=0+30;
	planeDataL[2]=0;
	planeDataL[3]=0;
	
	planeDataL[4]=w+30;
	planeDataL[5]=0+30;
	planeDataL[6]=1;
	planeDataL[7]=0;
	
	planeDataL[8]=0+30;
	planeDataL[9]=h+30;
	planeDataL[10]=0;
	planeDataL[11]=1;
	
	
	
	planeDataL[12]=w+30;
	planeDataL[13]=h+30;
	planeDataL[14]=1;
	planeDataL[15]=1;
    
    
    
    planeData[0]=0;
	planeData[1]=0;
	planeData[2]=0;
	planeData[3]=0;
	
	planeData[4]=w+60;
	planeData[5]=0;
	planeData[6]=1;
	planeData[7]=0;
	
	planeData[8]=0;
	planeData[9]=h+60;
	planeData[10]=0;
	planeData[11]=1;
	
	
	
	planeData[12]=w+60;
	planeData[13]=h+60;
	planeData[14]=1;
	planeData[15]=1;
    
    
    planeDataSmall[0]=0;
	planeDataSmall[1]=0;
	planeDataSmall[2]=0;
	planeDataSmall[3]=0;
	
	planeDataSmall[4]=(w+60)/2;
	planeDataSmall[5]=0;
	planeDataSmall[6]=1;
	planeDataSmall[7]=0;
	
	planeDataSmall[8]=0;
	planeDataSmall[9]=(h+60)/2;
	planeDataSmall[10]=0;
	planeDataSmall[11]=1;
	
	
	
	planeDataSmall[12]=(w+60)/2;
	planeDataSmall[13]=(h+60)/2;
	planeDataSmall[14]=1;
	planeDataSmall[15]=1;
    
    
    
    projectionMatrixLines =new GLfloat[16];
    projectionMatrixLines[0] =2.0/w;
    projectionMatrixLines[1] =0.0;
    projectionMatrixLines[2] =0.0;
    projectionMatrixLines[3] =-1;
    
    projectionMatrixLines[4] =0.0;
    projectionMatrixLines[5] =-2.0/h;
    projectionMatrixLines[6] =0.0;
    projectionMatrixLines[7] =1;
    
    projectionMatrixLines[8] =0.0;
    projectionMatrixLines[9] =0.0;
    projectionMatrixLines[10] =-1;
    projectionMatrixLines[11] =0.0;
    
    projectionMatrixLines[12] =0.0;
    projectionMatrixLines[13] =0.0;
    projectionMatrixLines[14] =0.0;
    projectionMatrixLines[15] =1;
    
    
    
    projectionMatrix =new GLfloat[16];
    projectionMatrix[0] =2.0/(w+60);
    projectionMatrix[1] =0.0;
    projectionMatrix[2] =0.0;
    projectionMatrix[3] =-1;
    
    projectionMatrix[4] =0.0;
    projectionMatrix[5] =-2.0/(h+60);
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
    
    
    
    
    float ofset =0;
    
	lineData[0] =(float)ofset;
	lineData[1] =(float)ofset;
    
	lineData[2] =(float)w-ofset;
	lineData[3] =(float)ofset;
    
    
	lineData[4] =(float)w-ofset;
	lineData[5] =(float)h-ofset;
	
	
	lineData[6] =(float)ofset;
	lineData[7] =(float)h-ofset;
	
	
    lineData[8] =(float)ofset;
	lineData[9] =(float)ofset;
	
	
    
    Matrix3D *m  =new Matrix3D;
    
    z =0;
    blurRadius =1000000;
    
    
    x = ((float)rand()/RAND_MAX-0.5)*1600*4;
    y = ((float)rand()/RAND_MAX-0.5)*800;
    setZ (-((float)rand()/RAND_MAX) *700 -100);//*500-400
    targetY =y;
    targetZ =z;
    
    speed = ((float)rand()/RAND_MAX-0.5)*3;
    
    
    
    m->translate(x, y, z);
    objectMatrix =  m->getRawData();
    
    
    glGenTextures(1, &lineTextureId);
    
	glBindTexture(GL_TEXTURE_2D, lineTextureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	
	glGenFramebuffersEXT(1, &fboIdLine);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboIdLine);
	
    
    
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
							  GL_TEXTURE_2D, lineTextureId, 0);
    
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    //DOF texture
    glGenTextures(1, &dofTextureId);
    
	glBindTexture(GL_TEXTURE_2D, dofTextureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w+60,h+60, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
    
	
	glGenFramebuffersEXT(1, &fboIdDOF);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboIdDOF);
	
    
    
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
							  GL_TEXTURE_2D, dofTextureId, 0);
    
    
    
    // DOF texture2
    glGenTextures(1, &dofTextureId2);
    
	glBindTexture(GL_TEXTURE_2D, dofTextureId2);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w+60,h+60, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
    
	glGenFramebuffersEXT(1, &fboIdDOF2);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboIdDOF2);
	
    
    
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
							  GL_TEXTURE_2D, dofTextureId2, 0);
    
    glBindTexture(GL_TEXTURE_2D,0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
}
void TextBase::update()
{
   
    float tempZ =z;
    tempZ+=(targetZ-tempZ)/100;
    
    setZ(tempZ);
    objectMatrix[3] =x;
    objectMatrix[7] =y;
    objectMatrix[11] =z;
    
    
}
void TextBase::setZ(float zPos)
{
    int tempBlurRadius = (int)-zPos-500 ;
    if(tempBlurRadius <1)
    {
        tempBlurRadius =1;
    }
    else
    {
        tempBlurRadius/=20;
        if(tempBlurRadius <1)
        {
            tempBlurRadius =1;
        }
        if(tempBlurRadius>30)tempBlurRadius =30;
        
    }
    
    if(blurRadius != tempBlurRadius)
    {
        isDirtyDOF =true;
        
        
        
        blurRadius =tempBlurRadius;
        
        GausianBlurFactory *fact = GausianBlurFactory::getInstance();
        
        dofKernel =fact->getKernel(blurRadius) ;
        offsetWidth = fact->getOffsetData(width+60,height+60,blurRadius,true) ;
        offsetHeight= fact->getOffsetData(width+60,height+60,blurRadius,false) ;
        kernalSize = blurRadius*2 +1;
        
        //cout<< "???"<<offsetWidth[0]<<" "<<offsetHeight[0]<<" " <<blurRadius<< " "<<kernalSize <<"\n";
    }
    
    
    z=zPos;
    
}


