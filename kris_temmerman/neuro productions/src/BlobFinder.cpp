//
//  BlobFinder.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 10/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "BlobFinder.h"



//--------------------------------------------------------------
BlobFinder::BlobFinder(){
	
	
	
    
	
    cubeCount =0;
    
    rawdataOutput =new unsigned char[ KINECT_SIZE];
    rawdataFilterd =new unsigned char[ KINECT_SIZE];
    nonEmptyPixelPos =0;
    
    int i;
    for(i=0;i< KINECT_SIZE;i++)
    {
        rawdataOutput[i] =0; 
        
    }
    test =0;
    
    
    
    stepSize =5;
    sw =KINECT_W/stepSize;
    sh  = KINECT_H/stepSize;
    numPoints =sw*sh;
    
  	points =new mcPoint[numPoints]; 
    
    
    int j;
    int count =0;
    for(i=0;i<sh;i++)
	{
        for (j=0; j<sw;j++) 
        {
            
            //points
            points[count].y = i*stepSize ;
            points[count].x = j*stepSize ;
            
            
          
            
            
            count++;
            
        }
        
        
	} 
    
    cubes =new mcCube[(sw-1) *(sh-1)];
  
    count =0;
 	for(i=0;i<sh-1;i++)
	{
        for (j=0; j<sw-1;j++) 
        {
            
            
            int pos = i*sw +j;
            cubes[count].tl = &points[pos];
            cubes[count].tr = &points[pos+1];
            
            cubes[count].bl = &points[pos+sw];
            cubes[count].br = &points[pos+1+sw];
            
        
            
            count++;
            
        }
        
        
	}

    
    
    
    
    
	
}

//--------------------------------------------------------------
void BlobFinder::update(float rawdataIn[KINECT_SIZE]){
   
    
  int i;
    for(i =0; i< KINECT_SIZE;i++)
    {
        
        rawdataOutput [i] =0;
        rawdata[i] =  rawdataIn[i];
        rawdataFilterd[i] =  rawdataIn[i];
       // chardata2[i] = (data[i]*255);
    }
   // std::memset ( rawdataOutput,0,sizeof(rawdataOutput)*360000);
    //std::memcpy( rawdata, rawdataIn, sizeof(rawdataIn)*360000); 
   
    nonEmptyPixelPos =0;
    int testcount = 0;
      while  ( findNextEmptyPixel())
    {
        
       
        int loopX = startX;
        int loopY = startY;
        //cout << loopX << " " << loopY << "\n";
        if( testcount == 2000){
            
           // cout << "failll, go next frame ";
            return;   
        }
        
        testcount = 0;
        
        int testvalOld;
        
        int minX  =loopX;
        int minY  =loopY;
        int maxX  =loopX;
        int maxY  =loopY;
        
        vector<int> pathData;// =new vector <int>;
        pathData.push_back(loopX);
        pathData.push_back(loopY);
        pathData.push_back(1);
        while ( testcount < 2000)
        {        
            int testVal  =0;
            //cout << testcount <<" " ;
            
            float chekValuePlus  =chekValue+100;
            float chekValueMin=chekValue-100;     
            if(chekValueMin<1)chekValueMin =1;
            else if(chekValuePlus<255)chekValuePlus =255;
            
            float pos1=rawdata[getArrPos(loopX,loopY)];
            float pos2=rawdata[getArrPos(loopX+1,loopY)];
           float pos4=rawdata[getArrPos(loopX,loopY+1)];
            float pos8=rawdata[getArrPos(loopX+1,loopY+1)];
            
            if(pos1!=0)testVal+=1;
             if(pos2!=0)testVal+=2;    
            if(pos4!=0)testVal+=4;  
           if(pos8!=0)testVal+=8;
            
           
       // cout << testVal<< " ";
            //y--
            if(testVal == 1) 
            {
                
                chekValue = rawdata[getArrPos(loopX,loopY)];
                loopY--;
            }
            else if (testVal ==5)
            {
                
                chekValue = rawdata[getArrPos(loopX,loopY)];
                loopY--;
            }
            else if (testVal ==9)
            {
                if(testvalOld ==2 || testvalOld ==3|| testvalOld ==11|| testvalOld ==7)
                {
                
                    chekValue = rawdata[getArrPos(loopX+1,loopY+1)];
                    loopY++;                
                }
                else{
                chekValue = rawdata[getArrPos(loopX,loopY)];
                loopY--;
                }
            }
            else if (testVal ==13)
            {
                
                chekValue = rawdata[getArrPos(loopX,loopY)];
                loopY--;
            }
           
            
            // y++
            else if (testVal ==8)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY+1)];
                loopY++;
            }
            else if (testVal ==10)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY+1)];
                loopY++;
                
            }
            else if (testVal ==11)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY+1)];
                loopY++;
            }
            
            
            
            //x++
            
            else if (testVal ==2)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY)];
                loopX++;
            }
            else if (testVal ==3)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY)];
                loopX++;
            }
            else if (testVal ==7)
            {
                
                chekValue = rawdata[getArrPos(loopX+1,loopY)];
                loopX++;
            }
            
            
            //x--
            else if (testVal ==4)
            {
                chekValue = rawdata[getArrPos(loopX,loopY+1)];
                loopX--;
                
            }
            else if (testVal ==12)
            {
                
                chekValue = rawdata[getArrPos(loopX,loopY+1)];
                loopX--; 
                
            }
            else if (testVal ==14)
            {
                
                chekValue = rawdata[getArrPos(loopX,loopY+1)];
                loopX--;
            } else if (testVal ==6)
            {
                if(testvalOld ==1 || testvalOld ==5 || testvalOld ==9 || testvalOld ==13 )
               {
                    chekValue = rawdata[getArrPos(loopX+1,loopY)];
                    loopX++;
                
                }else{
                
                chekValue = rawdata[getArrPos(loopX,loopY+1)];
                 loopX--;
                }
                
            }
            else{
                
               // cout << testVal<< " fail ";
                
                return;       
            }
            //if(testVal ==6 || testVal  ==9){
            //cout << chekValue<<"  " <<loopX<<" "<< loopY<<" "<< startX<<" "  << startY<<" t" <<testVal<<" t" <<testvalOld<<"\n " ;
            
            //}
            testvalOld =testVal;
           // if(testcount> 1000)
          
            if (loopX == startX && loopY ==startY) 
            {
                
              
                
                // last chek 
                if(loopX<minX)minX =loopX;
                if(loopX>maxX)maxX = loopX;
                if(loopY<minY)minY =loopY;
                if(loopY>maxY)maxY= loopY;   
                testcount++;
                
                
                
                int sizeX =maxX-minX;
                int sizeY =maxY -minY;                
                int vol =  sizeX * sizeY;
              
              //cout<< vol << "\n";
               
                int i;
                int j;
                int  oldVal; 
                int val; 
                
                bool isUsefull =false;
                if (vol>1000 && sizeY > 50)
                {
                
                    // nuttige blob?
                    
                    Blob *blob =new Blob(sizeX ,sizeY,pathData);
                    //cout<<"\n" << minX<<"  "  << maxX <<"  " <<minY<<"  "  << maxY << "  <-minmaxes \n";
                    blob->minX =minX-KINECT_W2;
                    blob->maxX =maxX-KINECT_W2;
                    blob->minY =minY-KINECT_H2;
                    blob->maxY =maxY-KINECT_H2;
                    
                    blobVector.push_back(blob);
                    
                    isUsefull =true;
                    //cout <<  blobVector.size();
                }
                if(isUsefull){
                
                for (j= minY-1 ;j<maxY+1;j++)
                {
                    oldVal =0;
                    int startX =-100;
                    for (i =minX-1;i<maxX+1;i++)
                    {
                        val =(int)rawdataOutput[   getArrPos(i,j)] ;
                        
                        if(val==255)rawdata[getArrPos(i,j)] =0;
                        
                        if (val==0 && oldVal ==255)
                        {
                            
                            startX =i;
                            
                            
                        }else if(startX != -100)
                        {
                            if  (val==255 && oldVal ==0 )
                            {
                                int k;
                                
                                
                                for (k=startX ; k<i;k++)
                                {
                                    rawdata[getArrPos(k,j)] =0;
                                    
                                }
                                startX =-100;
                                
                            }
                            
                        }
                        
                        oldVal =val;
                    }    
                    
                    
                }
                }
                
                else{
                    
                    for (j= minY-1 ;j<maxY+1;j++)
                    {
                        oldVal =0;
                        int startX =-100;
                        for (i =minX-1;i<maxX+1;i++)
                        {
                            val =(int)rawdataOutput[   getArrPos(i,j)] ;
                            
                            if(val==255){
                                int pos  =getArrPos(i,j);
                                rawdata[pos] =0;
                                rawdataFilterd[pos] =0;
                                
                            }
                            if (val==0 && oldVal ==255)
                            {
                                
                                startX =i;
                                
                                
                            }else if(startX != -100)
                            {
                                if  (val==255 && oldVal ==0 )
                                {
                                    int k;
                                    
                                    
                                    for (k=startX ; k<i;k++)
                                    {
                                        int pos  =getArrPos(k,j);
                                        rawdata[pos] =0;
                                        rawdataFilterd[pos] =0;
                                    }
                                    startX =-100;
                                    
                                }
                                
                            }
                            
                            oldVal =val;
                        }    
                        
                        
                    }
                }
             //inputImage.setFromPixels(rawdata,w, h, OF_IMAGE_GRAYSCALE, true); 
                
                
                break;
                
                
            }
            int pos = getArrPos(loopX,loopY);
           
            rawdataOutput[pos] =255;
            if(loopX<minX)minX =loopX;
            if(loopX>maxX)maxX = loopX;
            if(loopY<minY)minY =loopY;
            if(loopY>maxY)maxY= loopY; 
            pathData.push_back(loopX);
            pathData.push_back(loopY);
            pathData.push_back(chekValue);
            
            testcount++;
            
        }
        
    }
   //personHandler->setBlobs(blobVector);
   blobVector.clear();
  //cout<<"\n\n here*************************\n";
    
    
    
    unsigned char val;
    
    int pointPos;
    int x;
    int y;
    float zw;
     cubeCount =0;
    for(i=0;i<numPoints;i++)
    {
        x = points[i].x;
        y = points[i].y;
        pointPos=y * KINECT_W + x;
        val =rawdataFilterd[pointPos]; 
        
        
        // bm1
        if( val != 0)
        {
            
            points[i].isHit =true;
            
            
            
           
            points[i].zReal  =val *-3.137; 
            points[i].xReal = x-KINECT_W2;
            points[i].yReal = y-KINECT_H2;
            addCube(&points[i]);
            
            
        }else
        {
            points[i].isHit =false;
        }
        
               
    }

    triangleCount =0;
  
    
   //calculateTriangles(  cubes,points, rawdataFilterd);
       
    
   // personHandler->triangles =triangles;
    // personHandler->triangleCount =triangleCount;
    // personHandler->cubeCount =cubeCount;
    
   if (DEBUG_KRIS) outputImage.setFromPixels(rawdataFilterd, KINECT_W, KINECT_H, OF_IMAGE_GRAYSCALE, true) ;
    
    
    
    
}

//--------------------------------------------------------------
void BlobFinder::draw(){
    

    outputImage.draw (0,0,KINECT_W,KINECT_H);
}




bool BlobFinder::findNextEmptyPixel()
{
   
     
    while (nonEmptyPixelPos<KINECT_SIZE )
    {
        //cout << (int)rawdata[nonEmptyPixelPos] <<" ";
        if(rawdata[nonEmptyPixelPos]>1)
        {
            chekValue=rawdata[nonEmptyPixelPos];
            nonEmptyPixelPos--;
            
            startY =nonEmptyPixelPos/KINECT_W;
            startX = nonEmptyPixelPos-(startY*KINECT_W);
                     rawdataOutput[nonEmptyPixelPos] =255;
            
            return true ;
        }
        nonEmptyPixelPos++;
    }
    
    return false;
    
    
}

/*
 
 
 
 
 
 */
void BlobFinder::addCube(mcPoint *point)
{
    cubeCount++;
    if(cubeCount>500 || cubeCount<0)return;
    int pos =  cubeCount*3;
    cubesPos[pos] =point->xReal;
    cubesPos[pos+1] =-point->yReal;
    cubesPos[pos+2] =point->zReal;
    

};

void BlobFinder::calculateTriangles(  mcCube *cubes, mcPoint *points, unsigned char  *pixelData)
{
    
    
    
    int numCubes =(sw-1)*(sh-1);
    int i;
    
    cubeCount =0;
    for(i=0;i<numCubes;i++)
    {
       
        
        
        mcCube cube =cubes[i];
        int pos=0;
        if(cube.tl->isHit )pos+=1;
        if(cube.tr->isHit )pos+=2;
        if(cube.bl->isHit )pos+=4;
        if(cube.br->isHit )pos+=8;      
        
        if(pos == 0)
        {
            continue;
        }
        
       
        mcPoint point1; 
        mcPoint point2 ;
        mcPoint point3 ;
       
        if(pos == 15)
        {
            
            //addCube(cube.tl);
            addTriangle(cube.tl,cube.tr,cube.bl);
            addTriangle(cube.tr,cube.br,cube.bl);
        }
        
        else if(pos == 1)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.tl,cube.bl,false,pixelData);
             
            
            addTriangle(&point1,&point2,cube.tl);
        }
        
        else if(pos == 2)
        {
            
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            
            addTriangle(&point1,&point2,cube.tr);
            
        }
        else if(pos == 3)
        {
             
            point1 = getCrossPoint(cube.tl,cube.bl,false ,pixelData);
            point2 = getCrossPoint(cube.tr,cube.br,false,pixelData );
            
            addTriangle(cube.tl,cube.tr,&point1);
            addTriangle(cube.tr,&point2,&point1);
            
        }
        else if(pos == 4)
        {
          
            point1 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            point2= getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            addTriangle(&point1,&point2,cube.bl);
            
        }
        else if(pos == 5)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(cube.bl,&point1,&point2);
            addTriangle(cube.tl,&point1,cube.bl);
        }
        else if(pos == 8)
        {
           
            point1 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            addTriangle(&point1, cube.br,&point2);
            
        }
        else if(pos == 7)
        {
             
            
            addTriangle( cube.tl, cube.tr,cube.bl);   
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(&point1, &point2,cube.tr);
            addTriangle(&point2, cube.bl,cube.tr);        }
        else if(pos == 10)
        {
            
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            addTriangle(&point1,cube.tr ,&point2);
            addTriangle(cube.tr,cube.br,&point2);    
        }
        else if(pos == 7)
        {
            
            
            addTriangle( cube.tl, cube.tr,cube.bl); 
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(&point1, &point2,cube.tr);
            addTriangle(&point2, cube.bl,cube.tr); 
            
        }   
        else    if(pos == 11)
        {
            
            addTriangle( cube.tl, cube.tr,cube.br); 
            point1 = getCrossPoint(cube.tl,cube.bl,false,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true ,pixelData);
            
            addTriangle(&point1,cube.br ,&point2);
            addTriangle(&point1, cube.tl,cube.br);
            
        }
        
        else  if(pos == 12)
        {
            
            
            point2 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            point1 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            addTriangle(&point1, &point2,cube.bl);
            addTriangle(&point2, cube.br,cube.bl); 
            
        }   
        else  if(pos == 13)
        {
            
            
            addTriangle( cube.br, cube.bl,cube.tl); 
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            addTriangle(&point1,&point2,cube.br );
            addTriangle(&point1, cube.br,cube.tl);
            
        }
        else  if(pos == 14)
        {
            
            
            addTriangle( cube.bl, cube.tr,cube.br); 
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            
            
            
            addTriangle(&point1,cube.bl ,&point2);
            addTriangle(&point1, cube.tr,cube.bl);
        }
        else  if(pos == 6)
        {
            
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.tl,false ,pixelData);
            
            
            addTriangle( cube.tr, &point1,cube.bl); 
            addTriangle(  &point1,cube.bl,&point2); 
            
            
            
            
            point1 = getCrossPoint(cube.tr,cube.br,false ,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle( cube.tr, &point1,cube.bl); 
            addTriangle(  &point1,&point2,cube.bl); 
            
            
        }    else  if(pos == 9)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.tr,false ,pixelData);
            
            
            addTriangle( cube.tl, &point1,cube.br); 
            addTriangle(  &point1,&point2,cube.br); 
            
            
            
            
            point1 = getCrossPoint(cube.tl,cube.bl,false ,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            
            addTriangle( cube.tl,cube.br, &point1); 
            addTriangle(  &point1,cube.br,&point2); 
            
            
        }
        
    }
    
    
    
}


mcPoint BlobFinder::getCrossPoint(mcPoint *onPoint,mcPoint *ofPoint,bool isHorizontal,unsigned char *depthPixelsBack)
{
    
    mcPoint crossPoint;
    int xPos;
    int yPos;
    
    int step =1;
    xPos = onPoint->x;
    yPos = onPoint->y;
    bool found = false;
    int val;
    int count=0;
    
    if(isHorizontal)
    {
        if( onPoint->x > ofPoint->x) step=-1;
        while(!found)
        {
            count++;
            if(count>stepSize)found =true;
            xPos+=step;
            val =	 depthPixelsBack[yPos * KINECT_W + xPos];	
            
            if( val==0)
            {
                xPos-=step;
                val =	 depthPixelsBack[yPos * KINECT_W  + xPos];
                /*float zw = distancePixelsLookup [val];
                 crossPoint.zReal  = zw;
                 crossPoint.xReal = float((xPos - cx_d) * zw * fx_d);
                 crossPoint.yReal = float((yPos - cy_d) * zw * fy_d);*/
                found =true;
            }
            
        }
        
        
        
        
    }else
    {
        if( onPoint->y > ofPoint->y) step=-1;
        while(!found)
        {
            count++;
            if(count>stepSize)found=true;
            yPos+=step;
            val =	 depthPixelsBack[yPos * KINECT_W + xPos];	
            if( val ==0)
            {
                yPos-=step;
                val =	 depthPixelsBack[yPos * KINECT_W + xPos];
                /*float zw = distancePixelsLookup [val];
                 crossPoint.zReal  = zw;
                 crossPoint.xReal = float((xPos - cx_d) * zw * fx_d);
                 crossPoint.yReal = float((yPos - cy_d) * zw * fy_d);*/
                found =true;
            }
            
            
        }
        
        
    }
    
    
   
    
    //cout <<zw <<" ->"<<val <<" ";
    crossPoint.zReal =val *-3.137;
    crossPoint.xReal = xPos-KINECT_W2;
    crossPoint.yReal = yPos-KINECT_H2;
    
    crossPoint.x =xPos;
    crossPoint.y =yPos;
    return crossPoint;
}
void BlobFinder::addTriangle(mcPoint *point1,mcPoint *point2,mcPoint *point3)
{
           
    float  test1= point1->zReal -point2->zReal;
    if(test1 >Z_MARGE || test1 <-Z_MARGE)return;
    //cout << test1 << " ";
    test1= point1->zReal -point3->zReal;
    if(test1 >Z_MARGE || test1 <-Z_MARGE)return;
    //cout << test1 << " ";
    test1= point3->zReal -point2->zReal;
    if(test1 >Z_MARGE || test1 <-Z_MARGE)return;
    // cout << test1 << "\n";
    test1= point1->xReal -point2->xReal;
    if(test1 >XY_MARGE && test1 <-XY_MARGE)return;
    
    test1= point1->xReal -point3->xReal;
    if(test1 >XY_MARGE&& test1 <-XY_MARGE)return;
    
    test1= point3->xReal -point2->xReal;
    if(test1 >XY_MARGE && test1 <-XY_MARGE)return;
    
    test1= point1->yReal -point2->yReal;
    if(test1 >XY_MARGE && test1 <-XY_MARGE)return;
    
    test1= point1->yReal -point3->yReal;
    if(test1 >XY_MARGE && test1 <-XY_MARGE)return;
    
    test1= point3->yReal -point2->yReal;
    if(test1 >XY_MARGE && test1 <-XY_MARGE)return;
    
        //  if(triangleCount1>3000)return;
        
        
        triangles[triangleCount ] =point1->xReal;
        triangleCount++;
        triangles[triangleCount ] = point1->yReal;
        triangleCount++;
        triangles[triangleCount ] =point1->zReal;
        triangleCount++;
        
        
        triangles[triangleCount ] =  point2->xReal;
        triangleCount++;
        triangles[triangleCount ] = point2->yReal;
        triangleCount++;
        triangles[triangleCount ] =  point2->zReal;
        triangleCount++;
        
        
        triangles[triangleCount ] =  point3->xReal;
        triangleCount++;
        triangles[triangleCount ] =point3->yReal;
        triangleCount++;
        triangles[triangleCount ] = point3->zReal;
        triangleCount++;
 }
