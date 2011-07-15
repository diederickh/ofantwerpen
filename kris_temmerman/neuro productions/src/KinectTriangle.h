//
//  KinectTriangle.h
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#pragma once


#import "mcPoint.h"
class mcPoint;
class KinectTriangle
{
public:
    mcPoint *v1;
    mcPoint *v2;
    mcPoint *v3;

    void calcualteNormal();
    float xn;
    float yn;
    float zn;


};
    
