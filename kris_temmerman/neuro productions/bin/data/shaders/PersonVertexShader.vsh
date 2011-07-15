
  
//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//



uniform mat4 worldMatrix;
uniform mat4 perspMatrix;

attribute vec4 position;




varying float alpha;



void main()
{
	
	
	vec4 worldspace =position*worldMatrix;
   
      
    alpha = (worldspace.y+180.0)/360.0;
 
    gl_Position =worldspace*perspMatrix ;
    gl_Position.y *=-1.0;
}