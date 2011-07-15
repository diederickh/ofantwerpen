//
//  KinectHandler.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 28/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "KinectHandler.h"

#import <GLUT/GLUT.h>


enum {
	ATTRIB_VERTEX_FLAT
};



KinectHandler::KinectHandler()
{
   
    save =-1;


}
/*
*  constants
*
*/

double KinectHandler::fx_d = 1.0 / 5.9421434211923247e+02;
double KinectHandler::fy_d = 1.0 / 5.9104053696870778e+02;
float KinectHandler::cx_d = 3.3930780975300314e+02;
float KinectHandler::cy_d = 2.4273913761751615e+02;


int KinectHandler::width =640 ;
int KinectHandler::height=480 ;
int KinectHandler::stepSize=10;


unsigned short KinectHandler::maxDepth =600;//680;//487;
unsigned short KinectHandler::minDepth=0;


/*
 *
 *
 */


void KinectHandler::setup()
{
    int i;
    int j;
    
  
    triangleCount1 =0;
   
   
    
    wait =0;
	kinect.init();
	kinect.setVerbose(true);
	kinect.open();
	
	kinect1.init();
    kinect1.setVerbose(true);
    kinect1.open();
    
	kinect.setCameraTiltAngle(0);
    kinect1.setCameraTiltAngle(0);
	    // set real depth lookup
    calculateLookups();
    
    
    
    
    //prep marching cube points
    
    int count=0;
	
   
    blobFinder =new BlobFinder();
   
   
    sw =width/stepSize;
    sh  = height/stepSize;
    numPoints =sw*sh;

  	points1 =new mcPoint[numPoints]; 
       
    for(i=0;i<sh;i++)
	{
        for (j=0; j<sw;j++) 
        {
            
            //points
            points1[count].y = i*stepSize ;
            points1[count].x = j*stepSize ;
            
                     
            count++;
            
        }
        
        
	} 
     
    cubes1 =new mcCube[(sw-1) *(sh-1)];
       count =0;
	for(i=0;i<sh-1;i++)
	{
        for (j=0; j<sw-1;j++) 
        {
            
            
            int pos = i*sw +j;
            cubes1[count].tl = &points1[pos];
            cubes1[count].tr = &points1[pos+1];
            
            cubes1[count].bl = &points1[pos+sw];
            cubes1[count].br = &points1[pos+1+sw];
           
        
            
            count++;
            
        }
        
        
	}
    
    
    kinectShaderProgram =new KinectShaderProgram();
   
   
}




void KinectHandler::update()
{
    if(ofGetFrameNum()%2==1)
    {
       kinect.update();
    }else
    {
        kinect1.update();
    }
    int step =stepSize;
    int numX = width/step;
    int numY = height/step;
    
    int i;
    int j;
    unsigned short *depthPixelsBack1K = kinect.depthPixelsBack;
    unsigned short *depthPixelsBack2K = kinect1.depthPixelsBack;
    if(ofGetFrameNum()%2==1)
    {
    
        for (i=0; i<  307200;i++)
        {
       
        
        
            depthPixelsBack1[i] = depthPixelsBack1K[i];
      
        }
        
    }
    else
    {
    
      
            
            for (i=0; i<  307200;i++)
            {
                
                
                
                depthPixelsBack1[i] = depthPixelsBack2K[i];
                
            }
            
       
    
    }
        triangles.clear();
    points.clear();
   
       /*
        
        
        
        
        
        
        
        
        
        
        */
    
        /*
         *    prep mc point
         *    
         */
       
        int val1;
        int val2;
        int pointPos;
        int x;
        int y;
        float zw;
        
        for(i=0;i<numPoints;i++)
        {
            x = points1[i].x;
            y = points1[i].y;
            pointPos=y * width + x;
            val1 =depthPixelsBack1[pointPos];            
            if( val1 <maxDepth && val1>minDepth)
            {
                //cout <<val1 <<" ";
                
               
                
                
                
                
                points1[i].isHit =true;
                
                
                
                //cout << "ishit";
                
                zw = distancePixelsLookup [val1];
               points1[i].zReal  =zw; 
                points1[i].xReal = float((x - cx_d) * zw * fx_d);
                points1[i].yReal = float((y - cy_d) * zw * fy_d);
                ////if(points1[i].xReal>100)
             //cout<< points1[i].xReal <<" - " << points1[i].yReal<<" - " << points1[i].zReal<<" \n"; 
                
                
            }else
            {
                points1[i].isHit =false;
            }
          
            
        }
        triangleCount1 =0;
        
        
   // cout << triangleCount1;
       
        calculateTriangles(  cubes1, points1,depthPixelsBack1);
   /*
        int numPoints =points.size();
    float vertecArr[numPoints*6];  
        for(i =0;i<numPoints;i++)
        {
            mcPoint *point = points[i];
            point->calculateNormal();
            int pos =i*6;
            
            vertecArr[pos] =point->xReal;
            vertecArr[pos+1] =point->yReal;
            vertecArr[pos+2] =point->zReal;
            vertecArr[pos+3] =point->nx;
            vertecArr[pos+4] =point->ny;
            vertecArr[pos+5] =point->nz;

            

            
            
        }
    
        int numTriangles =triangles.size();
    cout << numPoints << " np /n";
        unsigned int indices[numTriangles*3];
        for (i=0;i<numTriangles;i++)
        {
            KinectTriangle *tri = triangles[i];
            int pos = i*3;
            indices[pos] =tri->v1->index;
            indices[pos+1] =tri->v2->index;
            indices[pos+2] =tri->v3->index;
          
    
        }
    */
   // cout <<  indices[20]<<"vert0 "<< " \n";
    
   // kinectShaderProgram->indices =indices;
    //kinectShaderProgram->vertices =vertecArr;
    //kinectShaderProgram->numIndices = numTriangles;
    //delete [] indices;
   // delete [] vertecArr;

       

 
    

}
void KinectHandler::draw()
{
    int i;
    int numPoints =points.size();
    float vertecArr[numPoints*6];  
    for(i =0;i<numPoints;i++)
    {
        mcPoint *point = points[i];
        point->calculateNormal();
        int pos =i*6;
        
        vertecArr[pos] =point->xReal;
        vertecArr[pos+1] =point->yReal;
        vertecArr[pos+2] =point->zReal;
        vertecArr[pos+3] =point->nx;
        vertecArr[pos+4] =point->ny;
        vertecArr[pos+5] =point->nz;
        
        
        
        
        
    }
    int numTriangles =triangles.size();
    int ind[numTriangles*3];
    
    //cout << numPoints << " np /n";
    unsigned int indices[numTriangles*3];
    for (i=0;i<numTriangles;i++)
    {
        KinectTriangle *tri = triangles[i];
        int pos = i*3;
        indices[pos] =tri->v1->index;
        indices[pos+1] =tri->v2->index;
        indices[pos+2] =tri->v3->index;
        
        ind[pos] =tri->v1->index;
        ind[pos+1] =tri->v2->index;
        ind[pos+2] =tri->v3->index;
       // cout << tri->v1->index<<" ";

        //cout << tri->v2->index<<" ";
        //cout <<tri->v3->index <<" ";
    }
    
    
    if(save>0 )
    {
    
        save--;
    
        stringstream ss;
        char cr = '\n';
        ss << "ply" << cr;
        ss << "format ascii 1.0" << cr;
        ss << "comment author: roxlu" << cr;
        ss << "comment object: auto generator with openFrameworks" << cr;
        ss << "element vertex " << numPoints<< cr;
        ss << "property float32 x" << cr;
        ss << "property float32 y" << cr;
        ss << "property float32 z" << cr;
              
        // ss << "property float32 red" << cr;
        // ss << "property float32 green" << cr;
        // ss << "property float32 blue" << cr;
        ss << "element face " << numPoints<< cr;
        ss << "property list uchar int vertex_indices " << cr;
        ss << "end_header" << cr;
        
        
        // VERTICES AND COLORS
        // -------------------------------------------
        ss << setprecision(5) << fixed;
        
      
        for(i =0;i<numPoints;i++)
        {
            mcPoint *point = points[i];
            point->calculateNormal();
            int pos =i*6;
            ss << vertecArr[pos]  << " "
            << vertecArr[pos+1]  << " "
            << vertecArr[pos+2]  << cr;
                       
            
            
            
            
        }
      
      
        for (i=0;i<numTriangles;i++)
        {
           
            int pos = i*3;
            ss << "3 "<<ind[pos] << " " << ind[pos+1]<<" "<<  ind[pos+2]<< cr;

            cout << " " <<ind[pos]<< " " <<(int)ind[pos+1]<< " " <<(int)ind[pos+2]<<cr;
            
        }
    
        string path =ofToDataPath("autoput",true);
        path+= ofToString(save);
        path+=".ply";
        ofstream ofs(path.c_str(), std::ios::trunc | std::ios::out);
        if(!ofs.is_open()) {
            cout << "error: cannot open file '" << path << "'" << endl;
            //return false;
        }
        ofs << ss.str();
        ofs.flush();
        ofs.close();
        cout<<"**********************************************************************" << path;
        //cout << vd.getNumColors() << "===" << vd.getNumVertices() << endl;
        //cout << ss.str() << endl;
        
    
    
    }
    
    
    
    
    
    // cout <<  indices[20]<<"vert0 "<< " \n";
    kinectShaderProgram->mouseX =(mouseX/1000*600 +800);
    kinectShaderProgram->indices =indices;
    kinectShaderProgram->vertices =vertecArr;
    kinectShaderProgram->numIndices = numTriangles;
   // cout << "  "<< triangleCount1 <<"\n";
    kinectShaderProgram->enable();
    kinectShaderProgram->renderData(triangles1,triangleCount1/3);
    kinectShaderProgram->disable ();


}
void KinectHandler::exit()
{

   
	kinect.close();
	
	
}


/*
 *
 *
 *
 *
 *     utils
 *
 *
 *
 *
 *
 *
 *
 */




void KinectHandler::calculateTriangles(  mcCube *cubes, mcPoint *points, unsigned short  *pixelData)
{
    
 
    
    int numCubes =(sw-1)*(sh-1);
    int i;
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
            
            
            addTriangle(cube.tl,cube.tr,cube.bl);
            addTriangle(cube.tr,cube.br,cube.bl);
        }

       else if(pos == 1)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.tl,cube.bl,false,pixelData);
            
            
            addTriangle(&point1,&point2,cube.tl);
           // delete &point1;
            //delete &point2;
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


mcPoint KinectHandler::getCrossPoint(mcPoint *onPoint,mcPoint *ofPoint,bool isHorizontal,unsigned short *depthPixelsBack)
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
            val =	 depthPixelsBack[yPos * width + xPos];	
           
            if(  val >maxDepth || val<minDepth)
            {
                xPos-=step;
                val =	 depthPixelsBack[yPos * width + xPos];
              
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
             val =	 depthPixelsBack[yPos * width + xPos];	
            if(  val >maxDepth || val<minDepth)
            {
                
                yPos-=step;
                val =	 depthPixelsBack[yPos * width + xPos];
                
            
             
                found =true;
            }
            
            
        }
        
        
    }
    
    
    float zw = distancePixelsLookup [val];
    
    crossPoint.x =xPos;
    crossPoint.y =yPos;
    
   
    crossPoint.zReal  = zw;
    crossPoint.xReal = float((xPos - cx_d) * zw * fx_d);
    crossPoint.yReal = float((yPos - cy_d) * zw * fy_d);
    
   
    return crossPoint;
}
void KinectHandler::addTriangle(mcPoint *point1,mcPoint *point2,mcPoint *point3)
{
    unsigned int i;
        
    unsigned int index1;
    unsigned int index2;
    unsigned int index3;
    
    //chekPoint1;
    bool found =false;
    //cout<< point1->zReal<<" ";
    //cout<< point2->zReal<<" ";
    //cout<< point3->zReal<<" << \n";
    
    for (i=0;i<points.size();i++)
    {
        if(points[i]->isEqual(*point1))
        {
            found =true;
            index1 =(unsigned int)i;
             
            break;
        }
    
    }
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        points.push_back(point );
        point->index =points.size()-1;
        point->zReal =point1->zReal;
        point->xReal =point1->xReal;
        point->yReal =point1->yReal;
        index1 =point->index;
        
    }
    
    
    //chekPoint1;
    found =false;
    
    for (i=0;i<points.size();i++)
    {
        if(points[i]->isEqual(*point2))
        {
            found =true;
            index2 =(unsigned int)i;
             //cout <<index2<<"<-i2 ";
            break;
        }
        
    }
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        points.push_back(point );
        
        point->index =points.size()-1;
        point->zReal =point2->zReal;
        point->xReal =point2->xReal;
        point->yReal =point2->yReal;
        
        index2 =point->index;
        
    }

    
    
    //chekPoint3;
    found =false;
    
    for (i=0;i<points.size();i++)
    {
        if(points[i]->isEqual(*point3))
        {
            found =true;
            index3 =(unsigned int)i;
           // cout << " index3Set->"<< index3;
                        break;
        }
        
    }
    
    
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        points.push_back(point );
        point->index =points.size()-1;
        point->zReal =point3->zReal;
        point->xReal =point3->xReal;
        point->yReal =point3->yReal;
        index3 =point->index;
        //cout << " indexPoint->"<< index3;
        
    }
    if(index2==index1)return;
    if(index3==index1)return;
    if(index3==index2)return;
    
    KinectTriangle *tri =new KinectTriangle();
    tri->v1 =points[index1];
     tri->v2 =points[index2];
     tri->v3 =points[index3];
    triangles.push_back(tri);
    tri->calcualteNormal();
    points[index1]->addTriangle(tri );
     points[index2]->addTriangle(tri );
     points[index3]->addTriangle(tri );
    //
    //
    //  OLD METHODE
    //
      // if(triangleCount1>9000)return;
    return;
        
        triangles1[triangleCount1 ] =point1->xReal;
        triangleCount1++;
        triangles1[triangleCount1 ] = point1->yReal;
        triangleCount1++;
        triangles1[triangleCount1 ] =point1->zReal;
        triangleCount1++;
  
 //   cout << point1->zReal<< " ";
        triangles1[triangleCount1 ] = point2->xReal;
        triangleCount1++;
        triangles1[triangleCount1 ] = point2->yReal;
        triangleCount1++;
        triangles1[triangleCount1 ] =  point2->zReal;
        triangleCount1++;
    
    
        triangles1[triangleCount1 ] =  point3->xReal;
        triangleCount1++;
        triangles1[triangleCount1 ] =point3->yReal;
        triangleCount1++;
        triangles1[triangleCount1 ] = point3->zReal;
        triangleCount1++;
        
    
    
}

void KinectHandler::calculateLookups() {

    //return;
    float
    k1 = 0.1236,
    k2 = 2842.5,
    k3 = 1.1863,
    k4 = 0.0370;
    
		for(int i = 0; i < 2048; i++){
			if(i == 2047) {
				distancePixelsLookup[i] = 0;
				
			} else {
				distancePixelsLookup[i] =(-1000 * (k1 * tanf(((i) / k2) + k3) - k4));
              if( distancePixelsLookup[i] <0)
				cout <<"lookup: "<< distancePixelsLookup[i] <<" "<< i <<"\n";
			}
       
		}
  
	


}