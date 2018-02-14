#version 330
in vec4 baseColor;
in vec2 uvCoords;
out vec4 fragColor;
void main( )
{
	fragColor = vec4(uvCoords,0,1);
} 
