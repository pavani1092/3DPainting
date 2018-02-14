#version 330

uniform sampler2D uvTexture;
uniform sampler2D mainTexture;
in vec4 baseColor;
in vec2 uvCoords;
in vec4 pos;
out vec4 fragColor;
void main( )
{
	vec4 point = texture2D( uvTexture, gl_FragCoord.xy/1024.0 );
	vec4 color = texture2D( mainTexture, point.xy );
	
	fragColor = point ;
	
} 
