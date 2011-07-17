#include "ofxKinect1.h"
#include "ofMain.h"

// pointer to this class for static callback member functions
ofxKinect1* thisKinect1 = NULL;



//--------------------------------------------------------------------
ofxKinect1::ofxKinect1()
{
	ofLog(OF_LOG_VERBOSE, "ofxKinect1: Creating ofxKinect1");
	cout<< "makingkinnext2";
	bVerbose 				= false;
	bUseTexture				= true;
	
	// set defaults
	bGrabberInited 			= false;
	depthPixelsRaw			= NULL;
	depthPixelsBack			= NULL;
	videoPixels		  		= NULL;
	videoPixelsBack			= NULL;
	
	bNeedsUpdate			= false;
	bUpdateTex				= false;
	
	kinectContext			= NULL;
	kinectDevice			= NULL;
	
	targetTiltAngleDeg		= 0;
	bTiltNeedsApplying		= false;
	
	thisKinect1 = this;
}

//--------------------------------------------------------------------
ofxKinect1::~ofxKinect1(){
	close();
	clear();
}

//--------------------------------------------------------------------
void ofxKinect1::setVerbose(bool bTalkToMe){
	bVerbose = bTalkToMe;
}

//---------------------------------------------------------------------------
unsigned char * ofxKinect1::getPixels(){
	return videoPixels;
}

//---------------------------------------------------------------------------
unsigned char	* ofxKinect1::getDepthPixels(){
	return calibration.getDepthPixels();
}

//---------------------------------------------------------------------------
unsigned short 	* ofxKinect1::getRawDepthPixels(){
	return depthPixelsBack;
}

//---------------------------------------------------------------------------
float* ofxKinect1::getDistancePixels() {
	return calibration.getDistancePixels();
}

//---------------------------------------------------------------------------
unsigned char * ofxKinect1::getCalibratedRGBPixels(){
	return calibration.getCalibratedRGBPixels(videoPixels);
}

//------------------------------------
ofTexture & ofxKinect1::getTextureReference(){
	if(!videoTex.bAllocated()){
		ofLog(OF_LOG_WARNING, "ofxKinect1: getTextureReference - texture is not allocated");
	}
	return videoTex;
}

//---------------------------------------------------------------------------
ofTexture & ofxKinect1::getDepthTextureReference(){
	if(!depthTex.bAllocated()){
		ofLog(OF_LOG_WARNING, "ofxKinect1: getDepthTextureReference - texture is not allocated");
	}
	return depthTex;
}

//--------------------------------------------------------------------
bool ofxKinect1::isFrameNew(){
	if(isThreadRunning()){
		return !bNeedsUpdate;
	}
	return false;	
}

//--------------------------------------------------------------------
bool ofxKinect1::open(){
	if(!bGrabberInited){
		ofLog(OF_LOG_WARNING, "ofxKinect1: Cannot open, init not called");
		return false;
	}
	
	int number_devices = freenect_num_devices(kinectContext);
    cout << "/n" <<number_devices<<" /n";
	if (number_devices < 1) {
		ofLog(OF_LOG_ERROR, "ofxKinect1: Did not find a device");
		return false;
	}
	
	if (freenect_open_device(kinectContext, &kinectDevice, 0) < 0) {
		//ofLog(OF_LOG_ERROR, "ofxKinect: Could not open device # 0 tru # 1");
		if (freenect_open_device(kinectContext, &kinectDevice, 1) < 0){
			//ofLog(OF_LOG_ERROR, "ofxKinect: Could not open device");
			return false;
		}
	} else{
		ofLog(OF_LOG_ERROR, "ofxKinect1: was able open device # 0");	
	}
	freenect_set_user(kinectDevice, this);
	freenect_set_depth_callback(kinectDevice, &grabDepthFrame);
	//freenect_set_video_callback(kinectDevice, &grabRgbFrame);
	
	startThread(true, false);	// blocking, not verbose
	
	return true;
}

//---------------------------------------------------------------------------
void ofxKinect1::close(){
	if(isThreadRunning()){
		waitForThread(true);
	}
	
	bNeedsUpdate	= false;
	bUpdateTex		= false;
}

//---------------------------------------------------------------------------
bool ofxKinect1::isConnected(){
	return isThreadRunning();
}

//We update the value here - but apply it in kinect thread.
//--------------------------------------------------------------------
bool ofxKinect1::setCameraTiltAngle(float angleInDegrees){
	
	if(!bGrabberInited){
		return false;
	}
	
	targetTiltAngleDeg = ofClamp(angleInDegrees,-30,30);
	bTiltNeedsApplying = true;
	
	return true;
}

//--------------------------------------------------------------------
bool ofxKinect1::init(bool infrared, bool setUseTexture){
	if(isConnected()){
		ofLog(OF_LOG_WARNING, "ofxKinect1: Do not call init while ofxKinect1 is running!");
		return false;
	}
	
	clear();
	
	bInfrared = infrared;
	bytespp = infrared?1:3;
	
	calibration.init(bytespp);
	
	bUseTexture = setUseTexture;
	
	int length = width*height;
	depthPixelsRaw = new unsigned short[length];
	depthPixelsBack = new unsigned short[length];
	
	videoPixels = new unsigned char[length*bytespp];
	videoPixelsBack = new unsigned char[length*bytespp];
	
	memset(depthPixelsRaw, 0, length*sizeof(unsigned short));
	memset(depthPixelsBack, 0, length*sizeof(unsigned short));
	
	memset(videoPixels, 0, length*bytespp*sizeof(unsigned char));
	memset(videoPixelsBack, 0, length*bytespp*sizeof(unsigned char));
	
	if(bUseTexture){
		depthTex.allocate(width, height, GL_LUMINANCE);
		videoTex.allocate(width, height, infrared?GL_LUMINANCE:GL_RGB);
	}
	
	if (freenect_init(&kinectContext, NULL) < 0){
		ofLog(OF_LOG_ERROR, "ofxKinect1: freenet_init failed");
		return false;
	}
	ofLog(OF_LOG_VERBOSE, "ofxKinect1: Inited");
	
	number_devices = freenect_num_devices(kinectContext);
	ofLog(OF_LOG_VERBOSE, "ofxKinect1: Number of Devices found: " + ofToString(number_devices));
	//cout<<"ofxKinect1: Number of Devices found: "<<ofToString(number_devices)<<endl;
	
	bGrabberInited = true;
	
	return bGrabberInited;
}

//---------------------------------------------------------------------------
void ofxKinect1::clear(){
	if(isConnected()){
		ofLog(OF_LOG_WARNING, "ofxKinect1: Do not call clear while ofxKinect1 is running!");
		return;
	}
	
	if(kinectContext != NULL){
		freenect_shutdown(kinectContext);
	}
	
	if(depthPixelsRaw != NULL){
		delete[] depthPixelsRaw; depthPixelsRaw = NULL;
		delete[] depthPixelsBack; depthPixelsBack = NULL;
		
		delete[] videoPixels; videoPixels = NULL;
		delete[] videoPixelsBack; videoPixelsBack = NULL;
	}
	
	depthTex.clear();
	videoTex.clear();
	calibration.clear();
	
	bGrabberInited = false;
}

//----------------------------------------------------------
void ofxKinect1::update(){
	if(!bGrabberInited){
		return;
	}
	
	if (!bNeedsUpdate){
		return;
	} else {
		bUpdateTex = true;
	}
	
	if ( this->lock() ) {
		int n = width * height;
		
		calibration.update(depthPixelsBack);
		memcpy(depthPixelsRaw,depthPixelsBack,n*sizeof(short));
		memcpy(videoPixels, videoPixelsBack, n * bytespp);
		
		//we have done the update
		bNeedsUpdate = false;
		
		this->unlock();
	}
	return;
	if(bUseTexture){
		depthTex.loadData(calibration.getDepthPixels(), width, height, GL_LUMINANCE);
		videoTex.loadData(videoPixels, width, height, bInfrared?GL_LUMINANCE:GL_RGB);
		bUpdateTex = false;
	}
}


//------------------------------------
float ofxKinect1::getDistanceAt(int x, int y) {
	return calibration.getDistanceAt(x,y);
}

//------------------------------------
float ofxKinect1::getDistanceAt(const ofPoint & p) {
	return calibration.getDistanceAt(p);
}

//------------------------------------
ofxVec3f ofxKinect1::getWorldCoordinateFor(int x, int y) {
	return calibration.getWorldCoordinateFor(x,y);
}


//------------------------------------
ofColor	ofxKinect1::getColorAt(int x, int y) {
	int index = (y * width + x) * bytespp;
	ofColor c;
	c.r = videoPixels[index + 0];
	c.g = videoPixels[index + (bytespp-1)/2];
	c.b = videoPixels[index + (bytespp-1)];
	c.a = 255;
	
	return c;
}

//------------------------------------
ofColor ofxKinect1::getColorAt(const ofPoint & p) {
	return getColorAt(p.x, p.y);
}

//------------------------------------
ofColor ofxKinect1::getCalibratedColorAt(int x, int y){
	return getColorAt(calibration.getCalibratedColorCoordAt(x,y));
}

//------------------------------------
ofColor ofxKinect1::getCalibratedColorAt(const ofPoint & p){
	return getColorAt(calibration.getCalibratedColorCoordAt(p));
}

//------------------------------------
void ofxKinect1::setUseTexture(bool bUse){
	bUseTexture = bUse;
}

//----------------------------------------------------------
void ofxKinect1::draw(float _x, float _y, float _w, float _h){
	if(bUseTexture) {
		videoTex.draw(_x, _y, _w, _h);
	}
}

//----------------------------------------------------------
void ofxKinect1::draw(float _x, float _y){
	draw(_x, _y, (float)width, (float)height);
}

//----------------------------------------------------------
void ofxKinect1::draw(const ofPoint & point){
	draw(point.x, point.y);
}

//----------------------------------------------------------
void ofxKinect1::drawDepth(const ofPoint & point){
	drawDepth(point.x, point.y);
}

//----------------------------------------------------------
void ofxKinect1::draw(const ofRectangle & rect){
	draw(rect.x, rect.y, rect.width, rect.height);
}

//----------------------------------------------------------
void ofxKinect1::drawDepth(const ofRectangle & rect){
	drawDepth(rect.x, rect.y, rect.width, rect.height);
}


//----------------------------------------------------------
void ofxKinect1::drawDepth(float _x, float _y, float _w, float _h){
	if(bUseTexture) {
		depthTex.draw(_x, _y, _w, _h);
	}
}

//---------------------------------------------------------------------------
void ofxKinect1::drawDepth(float _x, float _y){
	drawDepth(_x, _y, (float)width, (float)height);
}

//----------------------------------------------------------
float ofxKinect1::getHeight(){
	return (float)height;
}

//---------------------------------------------------------------------------
float ofxKinect1::getWidth(){
	return (float)width;
}

//---------------------------------------------------------------------------
ofPoint ofxKinect1::getRawAccel(){
	return rawAccel;
}

//---------------------------------------------------------------------------
ofPoint ofxKinect1::getMksAccel(){
	return mksAccel;
}

//---------------------------------------------------------------------------
void ofxKinect1::enableDepthNearValueWhite(bool bEnabled){
	calibration.enableDepthNearValueWhite(bEnabled);
}

//---------------------------------------------------------------------------
bool ofxKinect1::isDepthNearValueWhite(){
	return calibration.isDepthNearValueWhite();
}

/* ***** PRIVATE ***** */

//---------------------------------------------------------------------------
void ofxKinect1::grabDepthFrame(freenect_device *dev, void *depth, uint32_t timestamp) {
	if (thisKinect1->lock()) {
		try {
			memcpy(thisKinect1->depthPixelsBack, depth, FREENECT_DEPTH_11BIT_SIZE);
			thisKinect1->bNeedsUpdate = true;
		}
		catch(...) {
			ofLog(OF_LOG_ERROR, "ofxKinect1: Depth memcpy failed");
		}
		thisKinect1->unlock();
	} else {
		ofLog(OF_LOG_WARNING, "ofxKinect1: grabDepthFrame unable to lock mutex");
	}
}

//---------------------------------------------------------------------------
void ofxKinect1::grabRgbFrame(freenect_device *dev, void *rgb, uint32_t timestamp) {
	if (thisKinect1->lock()) {
		try {
			memcpy(thisKinect1->videoPixelsBack, rgb, thisKinect1->bInfrared?FREENECT_VIDEO_IR_8BIT_SIZE:FREENECT_VIDEO_RGB_SIZE);
			thisKinect1->bNeedsUpdate = true;
		}
		catch (...) {
			ofLog(OF_LOG_ERROR, "ofxKinect1: Rgb memcpy failed");
		}
		thisKinect1->unlock();
	} else {
		ofLog(OF_LOG_ERROR, "ofxKinect1: grabRgbFrame unable to lock mutex");
	}
}

//---------------------------------------------------------------------------
void ofxKinect1::threadedFunction(){	
	
	
	freenect_set_led(kinectDevice, LED_GREEN);
	freenect_set_video_format(kinectDevice, bInfrared?FREENECT_VIDEO_IR_8BIT:FREENECT_VIDEO_RGB);
	freenect_set_depth_format(kinectDevice, FREENECT_DEPTH_11BIT);
	
	ofLog(OF_LOG_VERBOSE, "ofxKinect1: Connection opened");
	
	freenect_start_depth(kinectDevice);
	freenect_start_video(kinectDevice);
	
	while(isThreadRunning()){
		if(bTiltNeedsApplying){
			freenect_set_tilt_degs(kinectDevice, targetTiltAngleDeg);
			bTiltNeedsApplying = false;
		}
		
		freenect_update_tilt_state(kinectDevice);
		freenect_raw_tilt_state * tilt = freenect_get_tilt_state(kinectDevice);
		
		rawAccel.set(tilt->accelerometer_x, tilt->accelerometer_y, tilt->accelerometer_z);
		
		double dx,dy,dz;
		freenect_get_mks_accel(tilt, &dx, &dy, &dz);
		mksAccel.set(dx, dy, dz);
		
		ofSleepMillis(10);
		
		//		printf("\r raw acceleration: %4d %4d %4d  mks acceleration: %4f %4f %4f", ax, ay, az, dx, dy, dz);
	}
	
	// finish up a tilt on exit
	if(bTiltNeedsApplying){
		freenect_set_tilt_degs(kinectDevice, targetTiltAngleDeg);
		bTiltNeedsApplying = false;
	}
	
	freenect_stop_depth(kinectDevice);
	freenect_stop_video(kinectDevice);
	freenect_set_led(kinectDevice, LED_YELLOW);
	
	freenect_close_device(kinectDevice);
	
	ofLog(OF_LOG_VERBOSE, "ofxKinect1: Connection closed");
}

//---------------------------------------------------------------------------
ofxKinectCalibration& ofxKinect1::getCalibration() {
	return calibration;
}
