//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//






varying vec4 normalVar;

void main()
{
   // float s =dot(normalVar, vec4(0.0,0.0,-1.0,1.0))
	gl_FragColor =normalVar;
}

