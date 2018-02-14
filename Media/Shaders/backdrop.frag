#version 330 core
// Fragment Shader – file "backdrop.frag"
//   - Should be called either solidColor or Position

in vec4 vertColor;
out vec4 out_Color;
uniform vec2 WindowSize;
float sigma = log(256.0)/0.25;
void main(void)
{
	/*float width = WindowSize[0];
	float height = WindowSize[1];
	float x =  gl_FragCoord.x/width;
	float y =  gl_FragCoord.y/height;
	float radiusSq = (x-0.5)*(x-0.5)+(y-0.5)*(y-0.5);
	float gaussvalue = exp(-sigma*radiusSq);
	out_Color =vertColor*gaussvalue;*/

	const float xScale = 1.0 / 4.0;
    const float yScale = 1.0 / 4.0;
    const vec4 scarlet = vec4(0.733, 0.2, 0.3, 1.0);
    const vec4 grey = vec4(0.4, 0.4, 0.4, 1.0);
    float x =  floor(xScale*gl_FragCoord.x);
    float y =  floor(yScale*gl_FragCoord.y);
    gl_FragColor = scarlet;
    if(mod(y,10.0) == 0.0)
       gl_FragColor = grey;
    if(mod(floor(y/10.0),2.0)==1.0){
		if(mod(x,20.0) == 0.0)
           gl_FragColor = grey;
       }else{
         if(mod(x+10.0,20.0) == 0.0)
			gl_FragColor = grey;
       }
	
}


