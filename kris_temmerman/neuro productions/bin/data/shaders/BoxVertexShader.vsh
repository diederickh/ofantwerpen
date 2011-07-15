
  
//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//

uniform mat4 scaleMatrix;
uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 perspMatrix;

attribute vec4 position;




varying float z;

void main()
{
    vec4 scaleSpace =position;
    //scaleSpace.z = scaleSpace.z * 1.0;//scaleMatrix;
	vec4 localspace  = position*objectMatrix ;
	vec4 worldspace =localspace*worldMatrix;
    

   

    gl_Position =worldspace*perspMatrix ;
    z =1.0-((-localspace.z -localspace.x/3.0)/1000.0);
    z =clamp(z,0.0,1.0);
}