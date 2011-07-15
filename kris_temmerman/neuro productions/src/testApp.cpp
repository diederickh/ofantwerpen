#include "testApp.h"
#include "btBulletDynamicsCommon.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofBackground(33,33,33);
   
   /* myfont.loadFont("Interstate Bold.ttf", 25,true,true,false);  
    myfont.setLineHeight(30);
    
    */
    
   
     
    ofSetFrameRate(60);
    

    
    
    
    kinectHandler =new KinectHandler();
    kinectHandler->setup();
    
       
   
    
       }

//--------------------------------------------------------------
void testApp::update() {
	
    
       
    
    kinectHandler->update();
     
    
	}

//--------------------------------------------------------------
void testApp::draw() {
   glEnable (GL_DEPTH_TEST);
 
kinectHandler->draw();
    
   // cout<<" " << ofGetFrameRate() << ":fps ";
    

}

void testApp::getMatrix()
{


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glTranslated(20,25,30);
   // glOrtho(-400,400,180,-180,0,6000);
    
   
    ofRotateY(-20) ;
    ofTranslate(0,0,0) ;

    
    
    float matrix[ 16 ];
    float fMatrix[ 16 ];
    glGetFloatv( GL_PROJECTION_MATRIX, fMatrix );
    matrix[0] =fMatrix[0];
    matrix[1] =fMatrix[4];
    matrix[2] =fMatrix[8];
    matrix[3] =fMatrix[12];
    
    matrix[4] =fMatrix[1];
    matrix[5] =fMatrix[5];
    matrix[6] =fMatrix[9];
    matrix[7] =fMatrix[13];
    
    matrix[8] =fMatrix[2];
    matrix[9] =fMatrix[6];
    matrix[10] =fMatrix[10];
    matrix[11] =fMatrix[14];
    
    matrix[12] =fMatrix[3];
    matrix[13]=fMatrix[7];
    matrix[14] =fMatrix[11];
    matrix[15] =fMatrix[15];
    
    cout<<" \n";
    cout  << matrix[0] <<" " << matrix[1] <<" "<< matrix[2] <<" "<< matrix[3] <<" \n";
    cout  << matrix[4] <<" " << matrix[5] <<" "<< matrix[6] <<" "<< matrix[7] <<" \n";
    cout  << matrix[8] <<" " << matrix[9] <<" "<< matrix[10] <<" "<< matrix[11] <<" \n";
    cout  << matrix[12] <<" " << matrix[13] <<" "<< matrix[14] <<" "<< matrix[15] <<" \n";


}

//--------------------------------------------------------------
void testApp::exit() {
      kinectHandler->exit();
	
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	
    
    kinectHandler->save =2;
    return;
    
    switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;
        case 's':
            
                      
/*
#define START_STATE 1
#define ATTRACT_STATE 100
#define KILL_ATRACT_STATE 101
            
#define BUMB_STATE 1001
            
            
			  mainModel->state =900;*/
			break;
	}
}


//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
kinectHandler->mouseX =x ;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

   // kinectHandler->mouseX =x ;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

    //renderer->windowResized(w, h);
}

