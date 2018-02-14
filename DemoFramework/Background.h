#pragma once
#include "OpenGL.h"
#include "ICommand.h"
#include "OpenGL.h"
#include "Color.h"
#include<iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "FileUtility.h"
namespace Crawfis
{
	namespace Graphics
	{
		class Background : public Collections::IGenericCommand
		{
		public:
			Background(Color& clearColor = Colors::Transparent, float clearDepth = 1.0f, ITextureDataObject* texture = 0)
			{
				this->clearColor = clearColor;
				this->clearDepth = clearDepth;
				this->texture = texture;
				init();
				initShaders();
			}

			char* loadFile(std::string fname, GLint &fSize)
			{
				return Crawfis::IO::FileUtility::File2CharArray(fname.c_str());
			}


			// printShaderInfoLog
			// From OpenGL Shading Language 3rd Edition, p215-216
			// Display (hopefully) useful error messages if shader fails to compile
			void printShaderInfoLog(GLint shader)
			{
				int infoLogLen = 0;
				int charsWritten = 0;
				GLchar *infoLog;

				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

				// should additionally check for OpenGL errors here

				if (infoLogLen > 0)
				{
					infoLog = new GLchar[infoLogLen];
					// error check for fail to allocate memory omitted
					glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
					std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
					delete[] infoLog;
				}

				// should additionally check for OpenGL errors here
			}

			void printProgramInfoLog(GLint program)
			{
				int infoLogLen = 0;
				int charsWritten = 0;
				GLchar *infoLog;

				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);

				// should additionally check for OpenGL errors here

				if (infoLogLen > 0)
				{
					infoLog = new GLchar[infoLogLen];
					// error check for fail to allocate memory omitted
					glGetProgramInfoLog(program, infoLogLen, &charsWritten, infoLog);
					std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
					delete[] infoLog;
				}

				// should additionally check for OpenGL errors here
			}




			void init(void)
			{
				GLuint VertexArrayID;
				glGenVertexArrays(1, &VertexArrayID);
				glBindVertexArray(VertexArrayID);

				// Generate 1 buffer, put the resulting identifier in vertexbuffer
				glGenBuffers(1, &vertexbuffer);
				// The following commands will talk about our 'vertexbuffer' buffer
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);


				glBindVertexArray(0);



				glGenBuffers(1, &texBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
				glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), tex_coord, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void createShader(char* vertexShader, char* fragmentShader, char* geometryShader = 0) {

				GLuint f, v, g;

				char *vs, *fs, *gs;

				v = glCreateShader(GL_VERTEX_SHADER);
				f = glCreateShader(GL_FRAGMENT_SHADER);

				// load shaders & get length of each
				GLint vlen;
				GLint flen;
				GLint glen;

				vs = loadFile(vertexShader, vlen);
				fs = loadFile(fragmentShader, flen);

				const char * vv = vs;
				const char * ff = fs;

				glShaderSource(v, 1, &vv, &vlen);
				glShaderSource(f, 1, &ff, &flen);

				GLint compiled;

				glCompileShader(v);
				glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
				if (!compiled)
				{
					std::cout << "Vertex shader not compiled." << std::endl;
					printShaderInfoLog(v);
				}

				glCompileShader(f);
				glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
				if (!compiled)
				{
					std::cout << "Fragment shader not compiled." << std::endl;
					printShaderInfoLog(f);
				}

				programID = glCreateProgram();

				glBindAttribLocation(programID, 0, "in_Position");

				glAttachShader(programID, v);
				glAttachShader(programID, f);

				//checking for geometry shader
				if (geometryShader != 0) {
					g = glCreateShader(GL_GEOMETRY_SHADER);
					gs = loadFile(geometryShader, glen);
					const char * gg = gs;
					glShaderSource(g, 1, &gg, &glen);
					glCompileShader(g);
					glGetShaderiv(g, GL_COMPILE_STATUS, &compiled);
					if (!compiled)
					{
						std::cout << "geometry shader not compiled." << std::endl;
						printShaderInfoLog(g);
					}

					glAttachShader(programID, g);
					delete[] gs;
				}

				delete[] vs; // dont forget to free allocated memory
				delete[] fs; // we allocated this in the loadFile function...

			}

			void initShaders(void)
			{
				createShader("..\\Media\\Shaders\\SimpleVertex.vert", "..\\Media\\Shaders\\SimpleFragment.frag");
				GLint res;
				glLinkProgram(programID);
				glGetProgramiv(programID, GL_LINK_STATUS, &res);
				if (!res)
				{
					std::cout << "Program not linked." << std::endl;
					printProgramInfoLog(programID);
				}
				SamplerApplicator* uniformBindingUV = new SamplerApplicator("texture");
				TextureBinding* bindingUV = TextureBindManager::Instance()->CreateBinding(texture, uniformBindingUV);
				bindingUV->Enable();
				bindingUV->Disable();

				int uniform_WindowSize = glGetUniformLocation(programID, "WindowSize");
				int constantLocation = glGetUniformLocation(programID, "texture");

				glUseProgram(programID);
				glUniform2f(uniform_WindowSize, 500, 500);
				if (constantLocation >= 0) {
					glUniform1i(constantLocation, (*uniformBindingUV).hardwareUnit);
				}
				
			}


			virtual void Execute()
			{
				int error = glGetError();
				if (error != 0) {
					std::cout << "hgj";
				}
				glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
				glClearDepthf(clearDepth);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
				error = glGetError();
				if (error != 0) {
					std::cout << "hgj";
				}

				//glActiveTexture(texture);
				//glBindTexture(GL_TEXTURE_2D, texture);

				error = glGetError();
				if (error != 0) {
					std::cout << "hgj";
				}

				//glutSwapBuffers();

				error = glGetError();
				if (error != 0) {
					std::cout << "hgj";
				}

			}
		private:
			Color clearColor;
			float clearDepth;

			// Globals
			// Real programs don't use globals :-D
			// Data would normally be read from files
			GLfloat vertices[8] = { -1.0f,1.0f,
				-1.0f,-1.0f,
				1.0f,1.0f,
				1.0f,-1.0f
			};

			unsigned int vaoCube, vertexbuffer, texBuffer, vboColors, vboIndices;

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
			unsigned int programID;
			ITextureDataObject* texture;

		};
	}
}