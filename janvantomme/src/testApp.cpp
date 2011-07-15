#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground( 0, 0, 0 );
    
    glEnable( GL_DEPTH_TEST );
    ofDisableArbTex();
    
    for ( int i = 0; i < NUM_PTS; i++ ) {
        pts[i].x = ofRandom( -75, 75 );
        pts[i].y = ofRandom( -75, 75 );
        pts[i].z = ofRandom( -75, 75 );
        
        if ( ofRandom( 1.0 ) > 0.5 ) {
            color[i].r = 1.0;
            color[i].g = 1.0;
            color[i].b = ofRandom( 1.0 );
            color[i].a = ofRandom( 1.0 );
        } else {
            color[i].r = ofRandom( 1.0 );
            color[i].g = 1.0;
            color[i].b = 1.0;
            color[i].a = ofRandom( 1.0 );
        }
    }
    
    ptsVbo.setVertexData( pts, NUM_PTS, GL_DYNAMIC_DRAW );
    ptsVbo.setColorData( color, NUM_PTS, GL_DYNAMIC_DRAW );
    
    glPointSize( 3.0 );

    shader.load( "shaders/displace.vert", "shaders/displace.frag" );
    
    colorMap.loadImage("colormap.jpg");
    
    quadratic = gluNewQuadric();
    gluQuadricTexture( quadratic, GL_TRUE );
    gluQuadricNormals( quadratic, GL_SMOOTH );

    light.setAmbientColor( ofColor( 0, 0, 0 ) );
    light.setPointLight();
    
    fbo.allocate( 2048, 1024, GL_RGBA, 0 );
    
    rot = 0;
    rotSpeed = 0.01;
        
}

//--------------------------------------------------------------
void testApp::update(){
    
    rot += rotSpeed; //ofMap( mouseX, 0, ofGetWidth(), 0.1, 2.0 );

    rotSpeed += 0.0001;
    
    for ( int i = 0; i < NUM_PTS; i++ ) {
        pts[i].x += ofRandom( -4, 4 );
        pts[i].y += ofRandom( -4, 4 );
        pts[i].z += ofRandom( -4, 4 );        
    }
    
    ptsVbo.setVertexData( pts, NUM_PTS, GL_DYNAMIC_DRAW );
    
    ofSetWindowTitle( ofToString( ofGetFrameRate() ) );
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // create noisemap
    noiseMap.allocate( 256, 256, OF_IMAGE_GRAYSCALE );
    for (int j = 0; j < noiseMap.height; j++ ) {
        for (int i = 0; i < noiseMap.width; i++ ) {
            noiseMap.getPixels()[ j * noiseMap.width + i ] = ofNoise( i * .01, ofGetFrameNum() / 100.0 ) * 255; 
        }
    }
    noiseMap.reloadTexture();
    
//    noiseMap.draw( 0, 0 );
    
    // create bumpmap and copy noisemap to it
    bumpMap.allocate( 512, 256, OF_IMAGE_GRAYSCALE );

    for (int i = 0; i < 256; i++ ) {
        for (int j = 0; j < 256; j++ ) {
            int c = noiseMap.getPixels()[ j * noiseMap.width + i];
            //cout << c << endl;
            bumpMap.setColor( i, j, ofColor( c ) );
        }
    }
    
    noiseMap.mirror( false, true );
    for (int i = 0; i < 256; i++ ) {
        for (int j = 0; j < 256; j++ ) {
            int c = noiseMap.getPixels()[ j * noiseMap.width + i];
            bumpMap.setColor( i + 256, j, ofColor( c ) );
        }
    }
 //   noiseMap.mirror( true, false );
/*
    noiseMap.mirror( false, true );
    for (int i = 0; i < 512; i++ ) {
        for (int j = 0; j < 256; j++ ) {
            int c = noiseMap.getPixels()[ j * noiseMap.width + i];
            bumpMap.setColor( i + 512, j, ofColor( c ) );
        }
    }
    noiseMap.mirror( false, true );

    noiseMap.mirror( true, true );
    for (int i = 0; i < 512; i++ ) {
        for (int j = 0; j < 256; j++ ) {
            int c = noiseMap.getPixels()[ j * noiseMap.width + i];
            bumpMap.setColor( i + 512, j + 256, ofColor( c ) );
        }
    }
//    noiseMap.mirror( false, true );
*/
 
    //bumpMap.draw( 0, 512 );
    
    
    
    glEnable( GL_DEPTH_TEST );
    ofPushMatrix();
    ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );

// BEGIN DRAW PARTICLES TO SCREEN
    
    ofEnableAlphaBlending();
    ofPushMatrix();
    ofRotate( rot, 1.0, 0.0, 0.0 );
    ptsVbo.draw( GL_POINTS, 0, NUM_PTS );
    ofPopMatrix();
    ofDisableAlphaBlending();

// END DRAW PARTICLES TO SCREEN
    
/*    ofEnableLighting();
    light.enable();
    light.setPosition( ofVec3f( 0, -800, 0 ) );
    light.customDraw(); */
    
    ofTexture &colorRef = colorMap.getTextureReference();
//    ofTexture &bumpRef = fbo.getTextureReference();
    ofTexture &bumpRef = bumpMap.getTextureReference();
    
// BEGIN DRAW SPHERE WITH SHADER    
    ofPushMatrix();
    ofRotate( rot, 0.1, 1.0, 0.0 );
    ofRotateX( -90 );
    
    shader.begin();
    shader.setUniformTexture( "colormap", colorRef, 1 );
    shader.setUniformTexture( "bumpmap", bumpRef, 2 );
    shader.setUniform1i( "maxHeight", 100 );

    gluSphere( quadratic, 150.0, 100, 100 ); // 200

    shader.end();
    ofPopMatrix();
// END DRAW SPHERE WITH SHADER    

    
/*    light.disable();
    ofDisableLighting(); */

    ofPopMatrix();
    glDisable( GL_DEPTH_TEST );
    
    if ( ofGetFrameNum() < 1500 ) {
        imageSaver.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        char fileName[255];
        sprintf( fileName, "displace-%i.png", ofGetFrameNum() );
        imageSaver.saveImage( fileName );
    }
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

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