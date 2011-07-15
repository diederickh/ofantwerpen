//
//  KinectVertex.h
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#pragma once




class KinectVertex {
    
public:
    KinectVertex();
    
    float x;
    float y;
    float z;
    
  
    float zFar;
    
    bool isBackGround;
    void setPosition(float xPos,float yPos,float zPos);
   

};