/*
 *  GLImageData.mm
 *  Cubes
 *
 *  Created by Kris Temmerman on 19/01/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#include "GLImageData.h"

GLuint GLImageData::setPath(string pathIn)
{
	ofImage image;
    image.loadImage(pathIn);
	
	GLuint textureID ;
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB,GL_UNSIGNED_BYTE, image.getPixels());
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
   
	return textureID ;
}