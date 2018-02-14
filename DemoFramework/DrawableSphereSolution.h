#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include "Vector.h"
#include <math.h>
#include <vector>

using namespace Crawfis::Math;

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableSphereSolution : public IDrawable
		{
		public:
			DrawableSphereSolution(int maxTriangles)
			{
				numberOfRefinements = (int) log2f((float)maxTriangles / 8.0f) / 2.0f;
				created = false;
			}
			virtual void Draw()
			{
				InternalDraw(currentLevel);
			}
			void setLevel(int level)
			{
				currentLevel = min(numberOfRefinements-1, max(0, level));;
			}
		private:
			void CreateSphere()
			{
				TesselateSphere();
				CreateOpenGLBuffers(); // should have had a base class or a container that separates these.
				setLevel(numberOfRefinements - 1);
			}
			void TesselateSphere()
			{
				// Create a tesellation of a sphere from a dual pyramid (4-sided).
				// Canonical sphere of radius one, centered at the origin.
				Vector3 top(0, 0, 1);
				Vector3 left(-1, 0, 0);
				Vector3 left2(-1, 0, 0);
				Vector3 back(0, -1, 0);
				Vector3 right(1, 0, 0);
				Vector3 front(0, 1, 0);
				Vector3 bottom(0, 0, -1);
				// Count the number of triangles for all levels.
				int numberOfTriangles = 8;
				int ncurrent = 8;
				for (int i = 1; i < numberOfRefinements; i++)
				{
					ncurrent *= 4;
					numberOfTriangles += ncurrent;
				}
				int numberOfVertices = 3 * numberOfTriangles;
				vertices.reserve(numberOfVertices);
				
				AddTriangle(left, front, top);
				AddTriangle(front, right, top);
				AddTriangle(right, back, top);
				AddTriangle(back, left2, top);
				AddTriangle(left, bottom, front);
				AddTriangle(front, bottom, right);
				AddTriangle(right, bottom, back);
				AddTriangle(back, bottom, left2);
				numberOfTriangles = 8;
				int currentTriangle = 0;
				levelOfDetails.push_back(currentTriangle);
				triangleCounts.push_back(numberOfTriangles);
				for (int level = 1; level < numberOfRefinements; level++)
				{
					for (int k = 0; k < numberOfTriangles; k++)
					{
						RefineTriangle(vertices[currentTriangle], vertices[currentTriangle + 1], vertices[currentTriangle + 2]);
						currentTriangle += 3;
					}
					numberOfTriangles *= 4;
					levelOfDetails.push_back(currentTriangle);
					triangleCounts.push_back(numberOfTriangles);
				}
				created = true;
			}
			void RefineTriangle(Vector3 v0, Vector3 v1, Vector3 v2)
			{
				Vector3 mid01 = 0.5f*(v0 + v1);
				mid01.normalize();
				Vector3 mid12 = 0.5f*(v1 + v2);
				mid12.normalize();
				Vector3 mid20 = 0.5f*(v2 + v0);
				mid20.normalize();

				AddTriangle(v0, mid01, mid20);
				AddTriangle(mid01, v1, mid12);
				AddTriangle(mid12, v2, mid20);
				AddTriangle(mid01, mid12, mid20);
			}
			void AddTriangle(Vector3 v0, Vector3 v1, Vector3 v2)
			{
				vertices.push_back(v0);
				vertices.push_back(v1);
				vertices.push_back(v2);
			}
			void CreateOpenGLBuffers()
			{
				// Create a Vertex Array Object to organize all of the bindings.
				glGenVertexArrays(1, &vaoSphere);
				glBindVertexArray(vaoSphere);

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
				glBufferData(GL_ARRAY_BUFFER, 3 * vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
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
				glBufferData(GL_ARRAY_BUFFER, 3 * vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2)                                                                                                  ;

				// Reset 
				glBindVertexArray(0);
			}
			void InternalDraw(int level)
			{
				if (!created)
				{
					CreateSphere();
				}
				//
				// Actually draw the sphere
				//
				int error = glGetError();
				glBindVertexArray(vaoSphere);
				glDrawArrays(GL_TRIANGLES, levelOfDetails[level], 3*triangleCounts[level]);
				error = glGetError();
			}
		private:
			bool created;
			int numberOfRefinements = 0;
			std::vector<Vector3> vertices;
			std::vector<int> levelOfDetails;
			std::vector<int> triangleCounts;
			int currentLevel = 0;
			unsigned int vaoSphere, vboVertices, vboNormals;
		};
	}
}