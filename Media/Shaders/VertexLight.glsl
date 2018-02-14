#version 330

struct LightSource
{
	vec4 position;
	vec4 color;
};

struct BasicMaterial
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
}; 

const int maxLights = 2;
uniform vec4 lightPositions[maxLights];
uniform vec4 lightColors[maxLights];
uniform BasicMaterial frontMaterial;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;
layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec3 inNormal;
out vec4 baseColor;

void PointLight(in int i, in vec3 eye, in vec3 ecPosition3, in vec3 normal,
		inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	float nDotVP;	// normal . light direction
	float nDotHV;	// normal . half vector
	float pf;		// power factor
	float attenuation;	// computed attenuation factor
	float d;			// distance from surface to light source
	vec3 VP;			// direction from surface to light position
	vec3 halfVector;	// direction of maximum highlights
	
	// Compute vector from surface to light position
	vec4 lightPosInCamera = modelViewMatrix * lightPositions[i];
	VP = vec3(lightPosInCamera) - ecPosition3;
	
	// Compute distance between surface and light position
	d = length(VP);
	
	// Compute attenuation
	attenuation = 1.0;
	
	//halfVector = normalize(VP + eye);
	halfVector = normalize(2*dot(normal,VP)*normal - VP);

	nDotVP = max(0.0, dot(normal,normalize(VP)));
	nDotHV = max(0.0, dot(normal, halfVector));
	
	if( nDotVP <= 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, frontMaterial.shininess);
	
	diffuse		+= lightColors[i] * nDotVP * attenuation;
	specular	+= lightColors[i] * pf * attenuation;
}


void DirectionalLight(in int i, in vec3 normal,
		inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	float nDotVP;	// normal . light direction
	float nDotHV;	// normal . half vector
	float pf;		// power factor
	
	//vec3 VP = lightPositions[i].xyz;
	vec3 VP = (normalMatrix * lightPositions[i]).xyz;
	vec3 halfVector = normalize(2*dot(normal,VP)*normal - VP);

	nDotVP = max(0.0, dot(normal,normalize(VP)));
	nDotHV = max(0.0, dot(normal, halfVector));
	
	if( nDotVP <= 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, frontMaterial.shininess);
	
	diffuse		+= lightColors[i] * nDotVP;
	specular	+= lightColors[i] * pf;
}

void main()
{
	vec4 ambient = vec4(0.0,0.0,0.0,0.0);
	vec4 diffuse = vec4(0.0,0.0,0.0,0.0);
	vec4 specular = vec4(0.0,0.0,0.0,0.0);
	
	// Calculate the eye position
	vec4 position = vec4(inPosition,1);
	vec4 ecPosition = modelViewMatrix * position;
	vec3 ecPosition3 = (vec3(ecPosition)) / ecPosition.w;
	vec3 eye = vec3(0,0,1);
    // transform vertex to clip space coordinates
    gl_Position = modelViewProjectionMatrix * position;
    // Calculate the lighting
    vec3 normal = normalize((normalMatrix * vec4(inNormal,0)).xyz);
    //vec3 normal = normalize(inPosition);
    for(int i=0; i <maxLights; i++)
    {
    	if(lightPositions[i].w <= 0.1)
    		DirectionalLight(i, normal, ambient, diffuse, specular);
    	else
    		PointLight(i, eye, ecPosition3, normal, ambient, diffuse, specular);
    }
    // Set the color
    baseColor = ambient* frontMaterial.ambient 
				+ diffuse * frontMaterial.diffuse
				+ specular*frontMaterial.specular;
    //baseColor = diffuse + specular;
    //baseColor.r = 1;
    baseColor.a = 1;
}
