/*
 *  mcPoint.cpp
 *  ofxKinect
 *
 *  Created by Kris Temmerman on 25/04/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#include "mcPoint.h"
#include "ofMain.h"


mcPoint::mcPoint()
{
    numTris =0;
    nx=0;
    ny=0;
    nz=0;
}
mcPoint::~mcPoint(){}
void mcPoint::calculateNormal()
{
   
    float size =sqrtf(nx*nx+ ny*ny + nz*nz);
    
    nx /= size;
    ny /= size;
    nz /= size;

    ///cout<< numTris<< " "<< size<<" " <<nx <<"  ->";

}
void mcPoint::addTriangle(KinectTriangle * tri)
{
    nx+= tri->xn;
    ny+= tri->yn;
    nz+= tri->zn;
    numTris++;
}
bool mcPoint::isEqual(mcPoint p)
{
    if(zReal != p.zReal)return false;
    if(xReal != p.xReal)return false;
    if (yReal !=p.yReal)return false;
    return true;

}

