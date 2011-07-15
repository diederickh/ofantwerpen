#include "testApp.h"

#define NUM_BYTES_IN_IMG (360 * 480 * 3)

//--------------------------------------------------------------
void testApp::setup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);

	//setup the server to listen on 11999
	tcpServer = new ofxTCPServer();
	tcpServer->setup(11999);
	
	pixels = new unsigned char[NUM_BYTES_IN_IMG];
	totalBytes = NUM_BYTES_IN_IMG;
	memset(pixels, 255, totalBytes);
	drawImage = false;
	
	elapasedTime = ofGetElapsedTimeMillis();
	loopIndex = 0;
	rowIndex = 0;
	pixelcount = 0;
	connectedClients = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
	int  bytesToGet = NUM_BYTES_IN_IMG;
	ofBackground(20, 20, 20);

	if (tcpServer->getNumClients() >  connectedClients) {
		// add new client
		grabberClient* newClient = new grabberClient();
		newClient->setup(connectedClients++,tcpServer);
		clients.push_back(newClient);
		cout << "added new client " << connectedClients << endl;
	}
	

	for (int clientIndex=0; clientIndex < clients.size(); clientIndex++) {
		grabberClient*  grabber = clients.at(clientIndex);
		grabber->update();
		
		if (grabber->imageFrameReady) {
			
			ofImage* capturedImage = new ofImage();
			capturedImage->setFromPixels(grabber->incomingPixels,480,360,OF_IMAGE_COLOR);
			images.push_back(capturedImage);
			grabber->imageFrameReady = false;
		}
	}
	
	
	if (ofGetElapsedTimeMillis() - elapasedTime > 100) {
		elapasedTime = ofGetElapsedTimeMillis();
		if(++loopIndex >= images.size())
		{
			loopIndex = 0;
		}
	}
	

}

//--------------------------------------------------------------
void testApp::draw(){

		
	ofSetHexColor(0xDDDDDD);
	ofDrawBitmapString("tcpServer SERVER Example \n\nconnect on port: "+ofToString(tcpServer->getPort()), 10, 20);
	ofDrawBitmapString("clients : "+ofToString(tcpServer->getNumClients()), 10, 30);

	ofSetHexColor(0x000000);
	ofRect(10, 60, ofGetWidth()-24, ofGetHeight() - 65 - 15);

	ofSetHexColor(0xDDDDDD);

	//for each connected client lets get the data being sent and lets print it to the screen
	for(int i = 0; i < tcpServer->getNumClients(); i++){

		//give each client its own color
		ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);

		//calculate where to draw the text
		int xPos = 15;
		int yPos = 80 + (12 * i * 4);

		//get the ip and port of the client
		string port = ofToString( tcpServer->getClientPort(i) );
		string ip   = tcpServer->getClientIP(0);
		string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
		
		//we only want to update the text we have recieved there is data
	}
	
	
	// Draw images
	ofSetColor(255, 255, 255);	

		
	if (images.size() > 0) {
		images[loopIndex]->draw(0,0);
	}
	
	int x =0;
	int y =360;
	
	for (int i=0; i < images.size(); i++) {
		if(x > ofGetWidth()){
			y += 100;
			x=0;
		}

		images[i]->draw(x,y,100,100);
		x+=100;

	}

//	ofDrawBitmapString("row index " + ofToString(rowIndex),0,0);
//	ofDrawBitmapString("tcpServer SERVER Example \n\nconnect on port: "+ofToString(tcpServer->getPort()), 10, 20);
	ofDrawBitmapString("clients : "+ofToString(tcpServer->getNumClients()), 10, 30);
	//ofDrawBitmapString("data rows : "+ofToString(rowIndex), 10, 40);	
	for (int clientIndex=0; clientIndex < clients.size(); clientIndex++) {
		grabberClient*  grabber = clients.at(clientIndex);
		grabber->draw();
	}	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key == 32)
	{
		images.clear();
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
