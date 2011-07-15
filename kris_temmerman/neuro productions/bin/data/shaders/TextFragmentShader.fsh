//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//


varying  vec2 text_cordsVarying;
uniform  sampler2D texture;

varying float z;


void main()
{

	
    vec4 color = texture2D (texture,text_cordsVarying);

	gl_FragColor =vec4(1,0,0,1);
}

