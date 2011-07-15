
  
//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//


uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 perspMatrix;
uniform float alpha_uni;
attribute vec4 position;

attribute vec2 text_cords;


varying vec2 text_cordsVarying;
varying vec4 colorVarying;

varying float alpha;

void main()
{
	
	vec4 localspace  = position*objectMatrix ;
	vec4 worldspace =localspace*worldMatrix;
    
    text_cordsVarying= text_cords;
   
   
    alpha =alpha_uni;
    
    gl_Position =worldspace*perspMatrix ;
   
}