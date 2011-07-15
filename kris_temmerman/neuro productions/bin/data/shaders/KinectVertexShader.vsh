
  
//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//


uniform mat4 worldMatrix;
uniform mat4 perspMatrix;
uniform mat4 objMatrix;
uniform mat4 normalMatrix;
uniform float off;

attribute vec4 position;

attribute vec4 normal;


varying vec4 normalVar;


void main()
{
    
	vec4 posOfset = 	position*objMatrix;
	vec4 worldspace =posOfset*worldMatrix;
    vec4 norm =normal*normalMatrix;
    normalVar = (normal+1.0)/2.0;    
    gl_Position =worldspace*perspMatrix ;
    
}