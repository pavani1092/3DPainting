#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableQuad : public IDrawable
		{
		public:
			DrawableQuad()
			{
			}
			virtual void Draw()
			{
				if (!created)
					CreateCube();
				int error = glGetError();
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					2,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
				// Draw the triangle !


				glEnableVertexAttribArray(3);
				glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
				glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(3);
			}
		private:
			void CreateCube()
			{
				GLuint VertexArrayID;
				glGenVertexArrays(1, &VertexArrayID);
				glBindVertexArray(VertexArrayID);

				// Generate 1 buffer, put the resulting identifier in vertexbuffer
				glGenBuffers(1, &vertexbuffer);
				// The following commands will talk about our 'vertexbuffer' buffer
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);


				glBindVertexArray(0);



				glGenBuffers(1, &texBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
				glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), tex_coord, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);


				created = true;
			}
		private:
			bool created = false;
			unsigned int vaoCube, vertexbuffer, texBuffer,vboColors, vboIndices;

			GLfloat g_vertex_buffer_data[8] = {
				-1.0f,1.0f,
				-1.0f,-1.0f,
				1.0f,1.0f,
				1.0f,-1.0f
			};

			GLfloat tex_coord[8] = {
				0,1,
				0,0,
				1,1,
				1,0
			};

		};
	}
}