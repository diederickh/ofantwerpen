
  


uniform mat4 projectionMatrix;

attribute vec4 position;

attribute vec2 text_cords;


varying vec2 text_cordsVarying;
varying vec4 colorVarying;



void main()
{
	
	vec4 rotationScene = position*projectionMatrix ;
	
   
   text_cordsVarying= text_cords;
   
    

    gl_Position =rotationScene ;
}