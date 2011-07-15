
  
//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//



uniform mat4 worldMatrix;
uniform mat4 perspMatrix;
uniform vec4 color;
attribute vec4 position;






varying vec4 col_var;

void main()
{
	
	
	vec4 worldspace =position*worldMatrix;
   
    col_var =color;


    gl_Position =worldspace*perspMatrix ;
   
}