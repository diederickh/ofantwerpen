//
//  KinectVertex.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "KinectVertex.h"
#include <iostream>

KinectVertex::KinectVertex()
{
    x  =0;
    y  =0;
    z = 0;
    zFar =-100;
    isBackGround =false;
}

void KinectVertex::setPosition(float xPos,float yPos,float zPos)
{
    x = xPos;
    y = yPos; 
    z=  zPos;
  
    if(z==0){
         isBackGround =true ;
        
        
        return;
    }
    isBackGround =false ;
    return;
       if( zFar -20> z )
        {
         isBackGround =false ;
            return;
        }
        if( zFar < z)
        {
            zFar  =z;
         
        }
  
    isBackGround =true;
  
  }
