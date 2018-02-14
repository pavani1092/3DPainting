#version 330 core
// Vertex Shader – file "PassThruFarPlane.vert"

in  vec2 in_Position;
uniform float brushSize;
uniform vec4 brushClr;
out vec4 color;
out vec3 uvCoord;
out float size;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform sampler2D uvTexture;

void main(void)
{
	vec4 pos = vec4(in_Position, 1.0, 1.0);
	uvCoord = texture2D( uvTexture, in_Position ).xyz;
	size = brushSize;
	color = brushClr ;
}


