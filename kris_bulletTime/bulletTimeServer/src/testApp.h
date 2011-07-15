#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "grabberClient.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofxTCPServer* tcpServer;

		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;

		vector <string> storeText;
	
	int totalBytes;
	int bytesRecieved;
	int rowIndex;
	int pixelcount;

	// need this to check if there's a new connection
	// probably not the best flow
	int connectedClients;
	
	int receivedCount;
	
	float elapasedTime;
	int loopIndex;
	
	unsigned char *pixels;
	vector<ofImage*> images;
	
	vector<grabberClient*>  clients;
	
	bool drawImage;
	
};

