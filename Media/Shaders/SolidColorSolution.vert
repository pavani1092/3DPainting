#version 330
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 defaultColor;
layout(location=0) in vec3 position;
layout(location=1) in vec4 color;
out vec4 baseColor;
void main()
{
    // transform vertex to clip space coordinates
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1);
    baseColor = color;
}
