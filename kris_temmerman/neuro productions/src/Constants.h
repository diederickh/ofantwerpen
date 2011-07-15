//
//  Constants.h
//  ofxKinect
//
//  Created by Kris Temmerman on 13/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#pragma once
//debug
#define DEBUG_KRIS 1
#define DEBUG_CUBES 0

#define NOISE_TEST 0

//

//kinect possitie
#define KINECT_START_ANGLE 20  //x as
#define KINECT_ROTATION2 18//y as/2
#define KINECT_START_HEIGHT -100



#define KINECT_CENTER_Y_ADJ 200

#define MAX_DEPTH 50
// kinect sizes
#define KINECT_W 800
#define KINECT_H 460
#define KINECT_W2 400
#define KINECT_H2 230
#define KINECT_SIZE KINECT_W *KINECT_H

#define BACKGROUND_FILTER_MARGIN 100

#define Z_MARGE 10
#define XY_MARGE 10


// vragen text en margins

#define TBFONT "Interstate Bold.ttf"
#define TBFONT_SIZE 25
#define TBFONT_LINEHEIGTH 30

#define BLUR_MARGIN 15
#define RECT_MARGIN 10
#define PIJL_HEIGHT 20
#define PIJL_WIDTH 20
#define PIJL_X 0

#define TEXT_CUBE_SCALE 0.1

//CAMERA

#define CAMERA_FOV 30

//STATES
// states meer dan 1000 zijn states met physics ingeschakeld

#define START_STATE 1
#define ATTRACT_STATE 100
#define KILL_ATRACT_STATE 101

#define ROTATE_STATE 102
#define KILL_ROTATE_STATE 103


#define BUMB_STATE 1001

