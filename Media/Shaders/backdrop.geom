#version 330 core 
in vec4 vertexColor[];
out vec4 vertColor;
layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;
void main(void)
{ 
       for (int i = 0; i < gl_in.length(); i++) {
              gl_Position = gl_in[i].gl_Position;
			  vertColor = vertexColor[i];
              EmitVertex() ;
       }
       EndPrimitive() ;
}

