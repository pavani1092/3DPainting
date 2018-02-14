#version 330 core
// Vertex Shader – file "backdrop.vert"

in  vec2 in_Position;
out vec4 vertexColor;

void main(void)
{
	gl_Position = vec4(in_Position, 1.0, 1.0);
	vertexColor = vec4(0.2,0.8,0.6,1.0);
}

