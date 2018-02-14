#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableCubeSolution : public IDrawable
		{
		public:
			DrawableCubeSolution()
			{
			}
			virtual void Draw()
			{
				if (!created)
					CreateCube();
				int error = glGetError();
				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBindVertexArray(vaoCube);
				glDrawElements(GL_TRIANGLES, 6*2*3, GL_UNSIGNED_SHORT, 0);
				error = glGetError();
			}
		private:
			void CreateCube()
			{
				// Create a Vertex Array Object to organize all of the bindings.
				glGenVertexArrays(1, &vaoCube);
				glBindVertexArray(vaoCube);

				// Steps:
				//  1) Create buffer for vertex positions
				//  2) Set vertex positions to be sent to the shaders at slot 0.
				//  3) Create buffer for colors
				//  4) Set colors to be sent to the shaders at slot 1.
				//  5) Create buffer for indices of the cube.
				//
				// Vertex positions
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboVertices);
				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, 6 * 4 * 3 * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				// Colors
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboColors);
				glBindBuffer(GL_ARRAY_BUFFER, vboColors);
				// Fill the buffer with the colors.
				glBufferData(GL_ARRAY_BUFFER, 6 * 4 * 4 * sizeof(GLfloat), &faceColors[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the color array's location for slot 1.
				glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				// Indices
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboIndices);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
				// Set the model data into the VBO.
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * 3 * sizeof(short), &indices[0], GL_STATIC_DRAW);

				// Reset 
				glBindVertexArray(0);
				created = true;
			}
		private:
			bool created = false;
			unsigned int vaoCube, vboVertices, vboColors, vboIndices;

			const float positions[6 * 4 * 3] = {
				// Front face
				-1.0, -1.0, 1.0,
					1.0, -1.0, 1.0,
					1.0, 1.0, 1.0,
					-1.0, 1.0, 1.0,

					// Back face
					-1.0, -1.0, -1.0,
					-1.0, 1.0, -1.0,
					1.0, 1.0, -1.0,
					1.0, -1.0, -1.0,

					// Top face
					-1.0, 1.0, -1.0,
					-1.0, 1.0, 1.0,
					1.0, 1.0, 1.0,
					1.0, 1.0, -1.0,

					// Bottom face
					-1.0, -1.0, -1.0,
					1.0, -1.0, -1.0,
					1.0, -1.0, 1.0,
					-1.0, -1.0, 1.0,

					// Right face
					1.0, -1.0, -1.0,
					1.0, 1.0, -1.0,
					1.0, 1.0, 1.0,
					1.0, -1.0, 1.0,

					// Left face
					-1.0, -1.0, -1.0,
					-1.0, -1.0, 1.0,
					-1.0, 1.0, 1.0,
					-1.0, 1.0, -1.0,
			};
			const short indices[6 * 2 * 3] = {
					0, 1, 2, 0, 2, 3,    // front
					4, 5, 6, 4, 6, 7,    // back
					8, 9, 10, 8, 10, 11,   // top
					12, 13, 14, 12, 14, 15,   // bottom
					16, 17, 18, 16, 18, 19,   // right
					20, 21, 22, 20, 22, 23,   // left
			};
			// Hmm. This may not work as it is an array of length 24 of arrays of length 4. Not sure the
			// memory will be contiguous.
			const Color faceColors[6*4] = { Colors::Grey, Colors::Grey, Colors::Grey, Colors::Grey, 
				Colors::Red, Colors::Red, Colors::Red, Colors::Red, 
				Colors::Yellow, Colors::Yellow, Colors::Yellow, Colors::Yellow, 
				Colors::White, Colors::White, Colors::White, Colors::White, 
				Colors::Brown, Colors::Brown, Colors::Brown, Colors::Brown, 
				Colors::Black, Colors::Black, Colors::Black, Colors::Black };
		};
	}
}