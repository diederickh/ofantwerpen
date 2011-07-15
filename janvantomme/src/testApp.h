#pragma once

#include "ofMain.h"

#define NUM_PTS 50000

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // points
        ofVbo ptsVbo;
        ofVec3f pts[NUM_PTS];
        ofFloatColor color[NUM_PTS];
    
        float rot;
        float rotSpeed;

        GLUquadricObj *quadratic;
    
        ofLight light;
    
        ofShader shader;
    
        ofImage colorMap;
        ofImage bumpMap;
        ofImage noiseMap;
    
        ofFbo fbo;
    
        ofImage imageSaver;
    
};
