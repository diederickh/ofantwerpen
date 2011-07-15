//
//
//  Created by Kris Temmerman on 29/11/10.
//  Copyright 2010 Neuro Productions. All rights reserved.
//


varying  vec2 text_cordsVarying;
uniform  sampler2D texture;

uniform  int kernalSize;
uniform vec2 offset[61];
uniform float scale[61];


void main()
{
    int i;
    vec3 sum =vec3(0,0,0);
    float sumAlpha;
    vec3 preAlpha;
    vec4 color;
	for(i =0;i<kernalSize;i++){
        vec2 textPos = text_cordsVarying+offset[i];
        color =texture2D (texture,textPos);
        preAlpha =color.rgb *(color.a);      
        sumAlpha += color.a *scale[i];
        sum+= preAlpha*scale[i];
    }
    sum/=sumAlpha;
    	gl_FragColor =vec4(1,1,1 ,sumAlpha) ;
}

