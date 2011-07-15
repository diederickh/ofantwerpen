//
//  KinectTriangle.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "KinectTriangle.h"
#import <GLUT/GLUT.h>
#include <iostream>

using namespace std;

void KinectTriangle::calcualteNormal()
{
    
    float  x1 =v1->xReal -v2->xReal;
    float  y1 =v1->yReal -v2->yReal;
    float  z1 =v1->zReal -v2->zReal;
    
    			
	float  x2 =v3->xReal -v2->xReal;
    float  y2 =v3->yReal -v2->yReal;
    float  z2 =v3->zReal -v2->zReal;
    
    float xc =y1*z2 -y2*z1;
    float yc = x1*z2 -x2*z1;
    float zc =x1*y2-x2*y1;
    
    float size =sqrtf(xc*xc +yc*yc +zc*zc);
    
    xn =xc/size;
    yn =yc/size;
    zn =zc/size;
    
}