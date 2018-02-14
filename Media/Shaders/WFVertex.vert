#version 330
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 defaultColor;
layout(location=0) in vec3 position;
layout(location = 3) in vec2 inTexCoords;
out vec4 baseColor;
void main()
{
    // transform vertex to clip space coordinates
    gl_Position = vec4(vec3(2*inTexCoords-1,0),1);
	baseColor = vec4(0.4,0.3,0.2,1.0);
}
