#version 330 core 

//precision highp float;
layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

in vec4 color[1];
in vec3 uvCoord[1];
in float size[1];
//in float delta[1];
out vec4 brushColor;
out vec2 texCoord;
void main(void)
{
	float delta = size[0];
	brushColor = color[0];
	if(uvCoord[0].z==0){
		vec4 center = vec4((2*uvCoord[0]-1),1.0);
		float left = center.x - delta;
		float right = center.x + delta;
		float bottom = center.y - delta;
		float top = center.y + delta;
		gl_Position = vec4(left, bottom, center.z, center.w);
		texCoord.x = 0;
		texCoord.y = 0;
		EmitVertex() ;
		gl_Position = vec4(right, bottom, center.z, center.w);
		texCoord.x = 1;
		EmitVertex() ;
		gl_Position = vec4(left, top, center.z, center.w);
		texCoord.x = 0;
		texCoord.y = 1;
		EmitVertex() ;
		gl_Position = vec4(right, top, center.z, center.w);
		texCoord.x = 1;
		EmitVertex() ;
	}
	
	EndPrimitive() ;
}

