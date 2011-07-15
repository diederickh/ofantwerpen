/*
 *  grabberClient.cpp
 *  networkTcpServerExample
 *
 *  Created by Kris Meeusen on 15/07/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#include "grabberClient.h"
#define NUM_BYTES_IN_IMG (360 * 480 * 3)


void grabberClient::setup(int number,ofxTCPServer* server)
{
	rowIndex = 0;
	pixelCount = 0;
	clientNumber = number;
	tcpServer = server;
	
	incomingPixels = new unsigned char[NUM_BYTES_IN_IMG];
	finishedImagePixels = new unsigned char[NUM_BYTES_IN_IMG];

	memset(incomingPixels, 255, NUM_BYTES_IN_IMG);
	memset(finishedImagePixels, 255, NUM_BYTES_IN_IMG);

}


void grabberClient::update()
{
//	return;
	
	if (!tcpServer->isClientConnected(clientNumber)) {
		return;
	}
	char tmpBuffer[480 *3];
	int numRecieved = tcpServer->receiveRawBytes(clientNumber,tmpBuffer, 480 *3);
		
	if( numRecieved > 0 ){
		for (int column=0; column < 480*3 ; column++) {
			incomingPixels[pixelCount] = tmpBuffer[column];
			pixelCount++;
		}
		
		cout<< clientNumber << ": incoming data row " << rowIndex << endl;
		rowIndex++;
	}
	
	if(rowIndex >= 360 ){
		cout << pixelCount;
		pixelCount = 0;
		ofImage* capturedImage = new ofImage();
		cout<< clientNumber << ": picture ready!"  << endl;
		rowIndex =0;
		
		imageFrameReady = true;
	}	
	 
}


void grabberClient::draw()
{	
	ofSetColor(90, 90, 90);
	ofRect(0, 12 * clientNumber, 360, 10);
	
	ofSetColor(255, 0, 0);
	ofRect(0, 12 * clientNumber, rowIndex, 10);	
}
