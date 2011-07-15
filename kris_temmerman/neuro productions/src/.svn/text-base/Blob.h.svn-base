//
//  Blob.h
//  ofxKinect
//
//  Created by Kris Temmerman on 11/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#pragma once
#include <vector>
#include  <iostream>
#include "Constants.h"

using namespace std; 
class Blob
{
       
public:
    float zSum;
    int w;
    int h;
   
    int minX;
    int maxX;
    int minY;
    int maxY; 
    
    float centerX;
    float centerY;
    float centerZ;
    
    
    int id;
    float r;
    float g;
    float b;
    
    int numIndices;
    float *data;
    Blob(int width,int height , vector<int> pathData);
    void setCenter();
    Blob();
    ~Blob();
    
    Blob clone();

};