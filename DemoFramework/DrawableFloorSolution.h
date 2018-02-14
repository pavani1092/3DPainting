#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include <vector>

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// A concrete drawable representing a simple flat mesh.
		// The orientation is in the xz plane.
		//
		class DrawableFloor : public IDrawable
		{
		public:
			//
			// Constructor.
			//
			DrawableFloor(int numHorizontalSamples, int numVerticalSamples) 
			{
				this->numHorizontalSamples = numHorizontalSamples;
				this->numVerticalSamples = numVerticalSamples;
				created = false;
			}
			//
			// Draw the floor.
			//
			virtual void Draw()
			{
				
				InternalDraw();
			}
		private:
			void CreateFloor()
			{
				stripSize = 2 * numHorizontalSamples;
				//vertices = new float*[numVerticalSamples-1];
				int index = 0;
				float y = 0.0f;
				float x = -1;
				float z = -1;
				float deltaX = 2.0f / (float) (numHorizontalSamples-1);
				float deltaZ = 2.0f / (float) (numVerticalSamples-1);
				float texOffset = 1;
				float texScale = 0.5f;
				for( int j = 0; j < (numVerticalSamples-1); j++ )
				{
					x = -1;
					//vertices[j] = new float[3*stripSize];
					index = 0;
					for( int i = 0; i < numHorizontalSamples; i++ )
					{
						vertices.push_back(x);
						vertices.push_back(y);
						vertices.push_back(z);
						normals.push_back(0);
						normals.push_back(1);
						normals.push_back(0);
						texCoords.push_back(texScale*(x+ texOffset));
						texCoords.push_back(texScale*(z+ texOffset));
						vertices.push_back(x);
						vertices.push_back(y);
						vertices.push_back(z + deltaZ);
						normals.push_back(0);
						normals.push_back(1);
						normals.push_back(0);
						texCoords.push_back(texScale*(x + texOffset));
						texCoords.push_back(texScale*(z + deltaZ + texOffset));
						x += deltaX;
					}
					z += deltaZ;
				}
				CreateOpenGLBuffers();
				created = true;
			}

			void CreateOpenGLBuffers()
			{				// Create a Vertex Array Object to organize all of the bindings.
				glGenVertexArrays(1, &vaoFloor);
				glBindVertexArray(vaoFloor);

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
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				// Normals
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboNormals);
				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);

				// Texture Coordinates
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboTexCoords);
				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), &texCoords[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(3);

				// Reset 
				glBindVertexArray(0);
			}
			void InternalDraw()
			{
				if (!created)
				{
					CreateFloor();
				}
				//
				// Actually draw the floor
				//
				glBindVertexArray(vaoFloor);
				for( int j=1; j < numVerticalSamples; j++ )
				{
					glDrawArrays(GL_TRIANGLE_STRIP, stripSize*(j-1), stripSize);
				}
				glBindVertexArray(0);
			}
		private:
			int numHorizontalSamples;
			int numVerticalSamples;
			bool created;
			std::vector<float> vertices;
			std::vector<float> normals;
			std::vector<float> texCoords;
			//float** vertices;
			int stripSize;
			unsigned int vaoFloor, vboVertices, vboNormals, vboTexCoords;
		};
	}
}