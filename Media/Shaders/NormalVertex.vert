#version 330


uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;
layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoords;
out vec2 uvCoords;
out vec3 ecPosition3;
out vec3 outNormal;

void main()
{
	// Calculate the eye position
	vec4 position = vec4(inPosition, 1);
	vec4 ecPosition = modelViewMatrix * position;
	ecPosition3 = (vec3(ecPosition)) / ecPosition.w;
	// transform vertex to clip space coordinates
	gl_Position = modelViewProjectionMatrix * position;
	// Calculate normal;
	outNormal = (normalMatrix * vec4(inNormal,0)).xyz;
	// Set the color
	uvCoords = inTexCoords;
}

