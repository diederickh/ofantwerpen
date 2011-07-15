#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxNetwork.h"
#define NUM_BYTES_IN_IMG (320 * 480 * 3)


class testApp : public ofxiPhoneApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void touchDown(ofTouchEventArgs &touch);
		void touchMoved(ofTouchEventArgs &touch);
		void touchUp(ofTouchEventArgs &touch);
		void touchDoubleTap(ofTouchEventArgs &touch);
		void touchCancelled(ofTouchEventArgs &touch);
		
		ofVideoGrabber grabber;
		ofTexture tex;
		unsigned char * pix;
		ofxTCPClient tcpClient;
	
	float counter;
	float lastBlinkTime;
	bool blinkOn;
	
	int connectTime;
	int deltaTime;
	int rowCount;
	
	bool weConnected;
	bool sendFrame;
	
	
	
	
	vector<unsigned char*> framesQueue;
	

};
