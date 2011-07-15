//
//  Blob.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 11/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "Blob.h"
Blob::Blob()
{
   
} 
Blob::Blob( int width, int height,vector<int> pathdata2)
{
    
    // cout << pathdata.size() << " <- num path vars \n";
    vector<int> pathdata;
    for(int i=0;i<pathdata2.size();i+=1)
    {
    
        pathdata.push_back(pathdata2[i]);
       // pathdata.push_back(pathdata2[i+1]);
        //pathdata.push_back(pathdata2[i+2]);
    }
    
    
    int len = pathdata.size()/3;
    int stepSearch =5;
    int margin  =stepSearch*2;
    
    
    
    float pathInX[len+margin*2];
    float pathInY[len+margin*2];
    float pathInZ[len+margin*2];
   
    for (int i=0; i<len; i++) {
        
        
        pathInX[i] = pathdata[i*3] ;
      //   cout <<i<< "-" << pathInX[i]<<"\n";
        pathInY[i] =  pathdata[i*3+1];
        pathInZ[i] =  pathdata[i*3+2];

    }
    for (int i=0;i<margin*2; i++)
    {
         //cout <<i<< "-" << pathInX[i]<<"\n";
        pathInX[len+i] =pathdata[i*3];
       //  cout <<len+i<< "--" << pathInX[len+i]<<"\n";
        pathInY[len+i] =pathdata[i*3+1];
        pathInZ[len+i] =pathdata[i*3+2];
    
    }
    float  pathOutX[len];
    float  pathOutY[len];
    float  pathOutZ[len];
    int pos,j; 
    float avX, avY,avZ;
  
    
    int i = len+margin;
    
    
    //cout << "*********************************\n";
    float devStep =1.0/ stepSearch;
    int stepOfz = (stepSearch-1)/2;
    while(i-- >margin){
        
            //cout <<i<< "?-" << pathInX[i]<<"\n";
        
            pos =i*2;
        
            j=stepSearch;
            avX = 0; avY = 0;avZ = 0;
            while(j--){
                
                
                avX += pathInX[i+stepOfz-j]; 
                avY += pathInY[i+stepOfz-j];
                avZ += pathInZ[i+stepOfz-j];
            }
            avX =devStep * avX; 
            avY =devStep * avY;
            avZ =devStep * avZ;
            pathOutX[i-margin] =((float)pathInX[i]+avX)/2.0;
            pathOutY[i-margin] =((float)pathInY[i]+avY )/2.0;
            pathOutZ[i-margin] =((float)pathInZ[i]+avZ)/2.0 ;
        
    }
    numIndices = len-1;
    data  =new float[(len-1)*3];
    zSum = 0;
    for (i= 0;i<len-1;i++)
    {
        data[3*i] = pathOutX[i+1]-KINECT_W2;
        data[3*i+1] = -(pathOutY[i+1]-KINECT_H2)  ;
        data[3*i+2] = - pathOutZ[i+1]*3.1;
        
    
        zSum += - pathOutZ[i+1]*3.1;
        
       //cout <<  data[3*i] << " " <<  data[3*i+1]<< " " <<  data[3*i+2] <<" -output" <<"\n";
    
    }
    zSum/=len-1;
    w =width;
    h=height;
}
Blob::~Blob()
{

   // delete [] data;
}

Blob Blob::clone()
{
    Blob *mijnBlob = new Blob();
    mijnBlob->w = w;
    mijnBlob->h= h;
    mijnBlob->zSum=zSum;
  ;
    
    mijnBlob->minX=minX;
    mijnBlob->maxX=maxX;
    mijnBlob->minY=minY;
    mijnBlob-> maxY=maxY;
    
    
    mijnBlob-> id=id;
    mijnBlob->r=r;
    mijnBlob->g=g;
    mijnBlob->b=b;
    
    mijnBlob->numIndices =numIndices;
    mijnBlob->data = data;
    
    
    
    return *mijnBlob;

}
void Blob::setCenter()
{
    centerX =(maxX+minX)/2;
 centerY =(maxY+minY)/2;
    centerZ =zSum;

}
