#pragma once

#include "ofMain.h"
#include "Constants.h"



#import "KinectHandler.h"





class testApp : public ofBaseApp {
    
    vector<string> vragen; // mag weg
public:
	
    
	void setup();
	void update();
	void draw();
	void exit();
	void getMatrix();
	
	void keyPressed  (int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
       
    KinectHandler *kinectHandler;
       
    	
};
