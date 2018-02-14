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
		class SetBackgroundCommand : public Collections::IGenericCommand
		{
		public:
			SetBackgroundCommand(Color& clearColor = Colors::Transparent, float clearDepth = 1.0f)
			{
				this->clearColor = clearColor;
				this->clearDepth = clearDepth;
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
				// Would load objects from file here - but using globals in this example	

				// Allocate Vertex Array Objects (get a handle or ID)
				glGenVertexArrays(1, &vertexArrayObjID);
				// Setup first Vertex Array Object
				glBindVertexArray(vertexArrayObjID);
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vertexBufferObjID);

				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
				// Define the layout of the vertex data.
				glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				// Reset 
				glBindVertexArray(0);

			
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
				createShader("..\\Media\\Shaders\\backdrop.vert", "..\\Media\\Shaders\\backdrop.frag", "..\\Media\\Shaders\\backdrop.geom");
				GLint res;
				glLinkProgram(programID);
				glGetProgramiv(programID, GL_LINK_STATUS, &res);
				if (!res)
				{
					std::cout << "Program not linked." << std::endl;
					printProgramInfoLog(programID);
				}

				int uniform_WindowSize = glGetUniformLocation(programID, "WindowSize");
				glUseProgram(programID);
				glUniform2f(uniform_WindowSize, 500, 500);
			}


			virtual void Execute()
			{
				//if (!isCleared) {
					glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
					glClearDepthf(clearDepth);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					isCleared = true;
				//}
				

				// Set the shader program
				glUseProgram(programID);
				// Draw the quad
				glBindVertexArray(vertexArrayObjID);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

				// Be nice and reset things back to the default.
				glBindVertexArray(0);
				glUseProgram(0);

				//glutSwapBuffers();



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

			// A vertex array object for the quad
			unsigned int vertexArrayObjID;
			// A vertex buffer object
			unsigned int vertexBufferObjID;
			// A Shader program
			unsigned int programID;
			bool isCleared = false;

		};
	}
}