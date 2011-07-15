//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//


varying  vec2 text_cordsVarying;
varying  float alpha;

uniform  sampler2D texture;

void main()
{

	
    vec4 color = texture2D (texture,text_cordsVarying);
    color.a *=alpha;
	gl_FragColor =color;
}

