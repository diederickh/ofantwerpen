//
//  KinectHandler.h
//  ofxKinect
//
//  Created by Kris Temmerman on 28/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#pragma once




#include "Constants.h" 
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxKinect1.h"

//#import "PersonHandler.h"

#import "KinectTriangle.h"
#import "KinectVertex.h"

#import "mcPoint.h"
#import "mcCube.h"

#import "BlobFinder.h"

#import "KinectShaderProgram.h"

class KinectHandler {
    
private:
    int numKinects;
    ofxKinect kinect;
	ofxKinect1 kinect1;
    
    
    static int width ;
	static int height ;
    static int stepSize ;
    
    
    
    static double fx_d;
	static double fy_d;
	static float cx_d;
	static float cy_d;
    
    float distancePixelsLookup[2048];

   
	static unsigned short maxDepth;
    static unsigned short minDepth;
    // pixel data
    unsigned short depthPixelsBack1[307200];
      unsigned short depthPixelsBack2[307200];
    
    
    
    // diepste pixel data voor background filtering
    unsigned short  depthPixelsVergelijk1[307200];
      
    
    vector<mcPoint *> points;
     vector<KinectTriangle *> triangles;    // triangulation
    
    mcPoint *points1;
    mcCube *cubes1;
    mcPoint *points2;
    mcCube *cubes2;
    
    float triangles1[390000];// max triangles *9 is gok
    int triangleCount1;
    
    
    
    bool isKinect1;
    
    int numPoints;
    int sw;
    int sh;
    
    // triangulation utils;
    void calculateTriangles(  mcCube *cubes, mcPoint *points, unsigned short *pixelData );
    void addTriangle(mcPoint *point1,mcPoint *point2,mcPoint *point3);
    mcPoint getCrossPoint(mcPoint *onPoint,mcPoint *ofPoint,bool isHorizontal,unsigned short *depthPixelsBack);
    
  
    
    // main app friends
   // PersonHandler *personHandler;
    
    
    KinectShaderProgram *kinectShaderProgram;
    
    
    // debug stuff
    int wait;
    float  rot;
    float  dir;
    ofImage testImage;
    
    BlobFinder *blobFinder ;
    
    
public:
	KinectHandler();
    
	void setup();
	void update();
	void draw();
	void exit();
	void calculateLookups();
	//void setPersonHandler(PersonHandler *_personHandler);

    
    GLuint FBOflatData ;
    
    float mouseX;
    int save;
    
    // temp test vars
	int numPersons;
};
