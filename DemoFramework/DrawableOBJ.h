
#pragma once
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
		class DrawableOBJ : public IDrawable
		{
		public:
			DrawableOBJ(char* filePath, bool isWireFrame = false)
			{
				created = false;
				path = filePath;
				isWireframe = isWireFrame;
			}
			virtual void Draw()
			{
				printError(2);
				InternalDraw();
			}

			void printError(int x) {
				int error = glGetError();
				if (error != 0) {
					std::cout << "error " << x << std::endl;
				}
			}
		private:
			void CreateObj()
			{
				FILE * file = fopen(path, "r");
				if (file == NULL) {
					std::cout << "Impossible to open the file !\n";
					return;
				}
				while (1) {

					char lineHeader[128];
					// read the first word of the line
					int res = fscanf(file, "%s", lineHeader);
					if (res == EOF)
						break;
					if (strcmp(lineHeader, "v") == 0) {
						Vector3 vertex;
						fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						temp_vertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "vt") == 0) {
						Vector2 uv;
						fscanf(file, "%f %f\n", &uv.x, &uv.y);
						temp_uvs.push_back(uv);
					}
					else if (strcmp(lineHeader, "vn") == 0) {
						Vector3 normal;
						fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
						temp_normals.push_back(normal);
					}
					else if (strcmp(lineHeader, "f") == 0) {
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
						int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
						if (matches != 6) {
							std::cout << "File can't be read by our simple parser : ( Try exporting with other options\n";
							return;
						}
						vertexIndices.push_back(vertexIndex[0]);
						vertexIndices.push_back(vertexIndex[1]);
						vertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
					}

				}
				

				std::cout << "OBJ file loaded successfully " << std::endl;

				for (unsigned int i = 0; i < vertexIndices.size(); i++) {
					unsigned int vertexIndex = vertexIndices[i];
					Vector3 vertex = temp_vertices[vertexIndex - 1];
					vertices.push_back(vertex);
				}
				for (unsigned int i = 0; i < uvIndices.size(); i++) {
					unsigned int uvIndex = uvIndices[i];
					Vector2 uv = temp_uvs[uvIndex - 1];
					uvs.push_back(uv);
				}
				for (unsigned int i = 0; i < normalIndices.size(); i++) {
					unsigned int normalIndex = normalIndices[i];
					Vector3 normal = temp_vertices[normalIndex - 1];
					normals.push_back(normal);
				}
				CreateOpenGLBuffers();
				
				created = true;
			}
			void CreateOpenGLBuffers()
			{
				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				/*if (isWireframe)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
				glGenVertexArrays(1, &vaoObj);
				glBindVertexArray(vaoObj);

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
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				/*
				// Normals
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboNormals);
				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);
				*/


				// Texture Coordinates
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vboTexCoords);
				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2), &uvs[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				// This also set's the vertex array's location for slot 0.
				glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(3);

				// Reset 
				glBindVertexArray(0);
				//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			void InternalDraw()
			{
				if (!created)
				{
					
					CreateObj();
					printError(1);
				}
				//
				// Actually draw the sphere
				//
				printError(3);
				glBindVertexArray(vaoObj);
				glDrawArrays(GL_TRIANGLES, 0, vertices.size());
			/*	if (isWireframe) {
					for (int i = 0; i < vertices.size(); i += 3)
						glDrawArrays(GL_LINE_LOOP, i, 3);
				}
				else {
					glDrawArrays(GL_TRIANGLES, 0, vertices.size());
				}*/
				
				glBindVertexArray(0);
				
			}
		private:
			bool created, isWireframe;
			char* path;
			std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
			std::vector< Vector3 > temp_vertices, vertices;
			std::vector< Vector2 > temp_uvs, uvs;
			std::vector< Vector3 > temp_normals, normals;
			unsigned int vaoObj, vboVertices, vboNormals, vboTexCoords;
		};
	}
}