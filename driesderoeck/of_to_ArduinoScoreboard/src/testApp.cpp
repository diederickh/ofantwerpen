#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	mySerial.setup("/dev/tty.usbserial-A7006x14",9600);
	counter = 0;
	counter2 = 0;
	
	TCP.setup(11999);
	
	ofSetVerticalSync(true);
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(20, 20, 20);
	
	//for each client lets send them a message letting them know what port they are connected on
/*	for(int i = 0; i < TCP.getNumClients(); i++){
		TCP.send(i, "hello client - you are connected on port - "+ofToString(TCP.getClientPort(i)) );
 }
*/

	string recgoals = TCP.receive(0);
	int goal = ofToInt(recgoals);
	
	if(goal == 1){
	counter++;
	word = "score ";
	word.append(ofToString(counter));
	word.append("-");
	word.append(ofToString(counter2));
	unsigned char* c_word = (unsigned char*)word.c_str();
	mySerial.writeByte(0x01);
	int len = word.size();
	
	mySerial.writeByte(len);
	for (int i = 0; i<len; i++) {
		mySerial.writeByte(c_word[i]);
	}
	
	mySerial.writeByte(0x02);
	}
	
	if(goal == 2){
		counter2++;
		word = "score ";
		word.append(ofToString(counter));
		word.append("-");
		word.append(ofToString(counter2));
		unsigned char* c_word = (unsigned char*)word.c_str();
		mySerial.writeByte(0x01);
		int len = word.size();
		
		mySerial.writeByte(len);
		for (int i = 0; i<len; i++) {
			mySerial.writeByte(c_word[i]);
		}
		
		mySerial.writeByte(0x02);
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetHexColor(0xDDDDDD);
	ofDrawBitmapString("TCP SERVER Example \n\nconnect on port: "+ofToString(TCP.getPort()), 10, 20);
	
	ofSetHexColor(0x000000);
	ofRect(10, 60, ofGetWidth()-24, ofGetHeight() - 65 - 15);
	
	ofSetHexColor(0xDDDDDD);
	
	//for each connected client lets get the data being sent and lets print it to the screen
	for(int i = 0; i < TCP.getNumClients(); i++){
		
		//give each client its own color
		ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
		
		//calculate where to draw the text
		int xPos = 15;
		int yPos = 80 + (12 * i * 4);
		
		//get the ip and port of the client
		string port = ofToString( TCP.getClientPort(i) );
		string ip   = TCP.getClientIP(i);
		string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
		
		
		//if we don't have a string allocated yet
		//lets create one
		if(i >= storeText.size() ){
			storeText.push_back( string() );
		}
		
		//we only want to update the text we have recieved there is data
		string str = TCP.receive(i);
		
		if(str.length() > 0){
			storeText[i] = str;
		}
		
		//draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);
		ofDrawBitmapString(storeText[i], 25, yPos + 20);

		
/*		word = str;
		unsigned char* c_word = (unsigned char*)word.c_str();
		mySerial.writeByte(0x01);
		int len = word.size();
		
		mySerial.writeByte(len);
		for (int i = 0; i<len; i++) {
			mySerial.writeByte(c_word[i]);
		}
		
		mySerial.writeByte(0x02);
*/		
	}
	

}
	 

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
/*	int scoreint = 1;
	char scorechar = '0' + scoreint;

	if (key=='a') {
		scoreint = scoreint + 1;
		mySerial.writeByte(scorechar);
		
	}
*/
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if (key=='a') {
		if (counter<9){
		counter++;
		word = "score ";
		word.append(ofToString(counter));
		word.append("-");
		word.append(ofToString(counter2));
		unsigned char* c_word = (unsigned char*)word.c_str();
		mySerial.writeByte(0x01);
		int len = word.size();
		
		mySerial.writeByte(len);
		for (int i = 0; i<len; i++) {
			mySerial.writeByte(c_word[i]);
		}
		
		mySerial.writeByte(0x02);
	
		}
		else{
		counter = 0;
		
		}
	}
	
	if (key == 'z') {
		if (counter2 <9){
		counter2++;
		word = "score ";
		word.append(ofToString(counter));
		word.append("-");
		word.append(ofToString(counter2));
		unsigned char* c_word = (unsigned char*)word.c_str();
		mySerial.writeByte(0x01);
		int len = word.size();
		
		mySerial.writeByte(len);
		for (int i = 0; i<len; i++) {
			mySerial.writeByte(c_word[i]);
		}
	
		mySerial.writeByte(0x02);
	    }
		else{
		counter2 = 0;
		}
	}
 
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