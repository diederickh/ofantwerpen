#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();

	noiseZ = 0;
	noiseScale = 0.005;
//	noiseScale = 1;

//	image.loadImage("pic.jpg");
//	image.loadImage("deze_als_test.png");
	image.loadImage("101_0985.jpg");
	
	gray.allocate(image.width, image.height);
	rgb.allocate(image.width, image.height);
	rgb.setFromPixels(image.getPixels(), image.width, image.height);
	gray = rgb;
	gray.threshold(75, true);
	gray.flagImageChanged();
	
	contourFinder.findContours(gray, 50, (image.width * image.height) / 2, 10, true);
	cout << "num blobs: " << contourFinder.nBlobs << endl;
	for (int i = 0; i < contourFinder.nBlobs; i++){
		for (int j = 0; j < contourFinder.blobs[i].pts.size(); j ++) {
			Node node = Node();
			node.setup(&image);
			node.setPosition(ofVec2f(contourFinder.blobs[i].pts[j].x, contourFinder.blobs[i].pts[j].y));
			nodes.push_back(node);
		}
	}
	
//	for (int y = 0; y < image.height; y += 60) {
//		for (int x = 0; x < image.width; x += 60) {
//			ofColor here = image.getColor(x, y);
////			if (here.getBrightness() < 200) {
//				Node node = Node();
//				node.setup(&image);
//				node.setPosition(ofVec2f(x, y));
//				nodes.push_back(node);
////			}
//		}
//	}
	
}

//--------------------------------------------------------------
void testApp::update(){

	noiseZ += 2 * noiseScale;
	
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
//	image.draw(10, 10, 100, 100);
	
	gray.draw(0, 0, 320, 240);

	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].noiseZ = noiseZ;
		nodes[i].noiseScale = noiseScale;
		nodes[i].draw();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 's'){
		ofSaveScreen(ofToString(ofGetYear()) + "-" + ofToString(ofGetMonth()) + "-" + ofToString(ofGetDay()) + "-" + ofToString(ofGetHours()) + "-" + ofToString(ofGetMinutes())  + "-" + ofToString(ofGetSeconds()) + ".jpg");
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