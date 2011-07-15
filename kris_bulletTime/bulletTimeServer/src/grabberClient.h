/*
 *  grabberClient.h
 *  networkTcpServerExample
 *
 *  Created by Kris Meeusen on 15/07/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "grabberClient.h"

class grabberClient {
	
	public:
		void setup(int number,ofxTCPServer* server);
		void update();
		void draw();
	
		unsigned char *finishedImagePixels;
		unsigned char *incomingPixels;
	
		ofxTCPServer* tcpServer;
		// client number
		int clientNumber;
	
		// incoming pixel row index
		int rowIndex;
		int pixelCount;
	
		bool imageFrameReady;
	
};
