#version 330
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 defaultColor;
layout(location=0) in vec3 position;
layout(location = 3) in vec2 inTexCoords;
out vec2 uvCoords;
out vec4 baseColor;
void main()
{
    // transform vertex to clip space coordinates
    gl_Position = projectionMatrix*modelViewMatrix*vec4(position,1);
    uvCoords = inTexCoords;
	baseColor = vec4(0.1,0.9,0.1,1.0);
}
