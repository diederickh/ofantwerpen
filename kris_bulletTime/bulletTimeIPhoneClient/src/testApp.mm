#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	ofSetFrameRate(30);

	// register touch events
	ofRegisterTouchEvents(this);
	
	grabber.initGrabber(480, 360, OF_PIXELS_RGB);
	grabber.setVerbose(true);
	//tex.allocate(grabber.getWidth(), grabber.getHeight(), GL_RGB);
	//pix = new unsigned char[ (int)( grabber.getWidth() * grabber.getHeight() * 3.0) ];
	
	weConnected = tcpClient.setup("192.168.1.102", 11999,true);
	
	connectTime = 0;
	deltaTime = 0;
	rowCount = 0;
//	tcpClient.setVerbose(true);
	sendFrame = false;
	
	lastBlinkTime = ofGetElapsedTimeMillis();
	blinkOn = true;
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(255,255,255);	
	
	grabber.update();
	
	if (framesQueue.size() > 0) {
		unsigned char* data = framesQueue[0];
		unsigned char* line = new unsigned char[480 *3];	
		
		//for (int row=0; row < 360; row++) {
			memcpy(line, data + (rowCount*(480*3)), 480*3*sizeof(unsigned char));
			tcpClient.sendRawBytes((const char*) line,480*3);
			rowCount++;
		//}
		
		if (rowCount >= 360) {
			framesQueue.erase(framesQueue.begin(),framesQueue.begin() +1);
			rowCount =0;
		}
		sendFrame = false;		
	}
	
	if (ofGetElapsedTimeMillis() - lastBlinkTime > 500) {
		blinkOn = !blinkOn;
		lastBlinkTime = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void testApp::draw(){	
	
	if (sendFrame) {
		ofSetColor(255, 255, 255);
		//ofRect(0, 0, getWidth(), getHeight()));
		ofDrawBitmapString("SENDING ",ofGetWidth()/2,ofGetHeight()/2);
		return;
	}
	
	ofSetColor(255);
	grabber.draw(0, 0);
	
	
	if(weConnected && blinkOn)
	{
		ofSetColor(0, 255, 0);
		ofRect(0, 0, 20, 20);
		
		ofDrawBitmapString("ONLINE ",30,0);

	}
	
	//ofDrawBitmapString("rowcount " + ofToString(rowCount), 15, 30);
	//ofDrawBitmapString(ofToString(grabber.getWidth()) + " " + ofToString(grabber.getHeight()) ,10,10);

		
	ofSetColor(0, 0, 0);
	ofRect(ofGetWidth()/2 - 7, ofGetHeight()/2 - 22, 14, 44);
	ofRect(ofGetWidth()/2 - 22, ofGetHeight()/2 - 7, 44, 14);
	
	ofSetColor(255, 255, 255);
	ofRect(ofGetWidth()/2 - 5, ofGetHeight()/2 - 20, 10, 40);
	ofRect(ofGetWidth()/2 - 20, ofGetHeight()/2 - 5, 40, 10);
	
	ofSetColor(255, 0, 0);
	ofRect(0, 0, rowCount * 480 /360, ofGetHeight());


	//tex.draw(0, 0, tex.getWidth() / 4, tex.getHeight() / 4);
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){

	//frame.setFromPixels(tester.getPixels(),360,480);
	//int rowLength = grabber.width * 3; 	
	sendFrame = true;
	
	unsigned char* tempFrame = new unsigned char[480 * 360 *3];	
	memcpy(tempFrame, grabber.getPixels() , 360 * 480*3*sizeof(unsigned char));

	framesQueue.push_back(tempFrame);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){

}


