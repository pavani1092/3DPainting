#pragma once
#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include "Color.h"
#include "IMouseHandler.h"
#include "IKeyboardHandler.h"
#include <vector>

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableBrushPath : public IDrawable, public Crawfis::Controller::IMouseHandler, public Crawfis::Controller::IKeyboardHandler
		{
		public:
			DrawableBrushPath()
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			virtual void Draw()
			{
				if (paintingMode) {
					if (!created)
						CreatePath();
					//std::cout << "path sizzeeee " << brushPath.size() << std::endl;
					if (brushPath.size() <= 0)
						return;

					// Draw the brush strokes
					// Bind the Vertex Array, which sets up the vertex attribute pointers.
					glBindVertexArray(vaoBrushPath);
					// Update the brush data.
					// Note that we do not need to bind the VertexAttribPointer, since we are 
					// not changing the association.
					glBindBuffer(GL_ARRAY_BUFFER, vboBrushPath);
					glBufferSubData(GL_ARRAY_BUFFER, 0, brushPath.size() * sizeof(GLfloat), &brushPath[0]);
					// Draw the Brush stroke.
					glDrawArrays(GL_POINTS, 0, brushPath.size() / 2);
					

					// Be nice and reset things back to the default.
					glBindVertexArray(0);
					//brushPath.clear();
				}
				

			}
		private:
			void CreatePath()
			{
				//std::cout << "createeee" << std::endl;
				glGenVertexArrays(1, &vaoBrushPath);
				glBindVertexArray(vaoBrushPath);

				// Generate 1 buffer, put the resulting identifier in vertexbuffer
				glGenBuffers(1, &vboBrushPath);
				// The following commands will talk about our 'vertexbuffer' buffer
				glBindBuffer(GL_ARRAY_BUFFER, vboBrushPath);
				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, Max_Points * sizeof(GLfloat), 0, GL_DYNAMIC_DRAW);

				glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);
				glBindVertexArray(0);



				created = true;
			}

			virtual void KeyPress(unsigned char key, int x, int y)
			{
				switch(key)
				{
					case 'p':
						paintingMode = true;
						break;
					case 'c':
						paintingMode = false;
						break;

				}
			}
			//
			// Handle the arrow keys and numeric keypad.
			//
			virtual void NumPadPress(int key, int x, int y)
			{
			}

			virtual void MouseEvent(int button, int state, int ix, int iy)
			{
				if (button == GLUT_LEFT_BUTTON && paintingMode)
				{
					float x, y;
					MapMouse(ix, iy, x, y);
					if (state == GLUT_DOWN)
					{
						isPainting = true;
						brushPath.clear();
						//std::cout << "painting "<< std::endl;
					}
					else
					{
						isPainting = false;
						Draw();
						//std::cout << "not painting "<<brushPath.size() << std::endl;
					}
				}
			}
			//
			// Handle any mouseMove events. Note, with GLUT this 
			// is only called when a mouse button is pressed by
			// default.
			//
			virtual void MouseMoved(int ix, int iy)
			{
				if (isPainting)
				{
					if (brushPath.size() > Max_Points) {
						//std::cout << "clearing "<<std::endl;
						brushPath.clear();
					}
					float x, y;
					//std::cout << "pushing "<<std::endl;
					if (ix <= 600 && iy <= 600) {
						MapMouse(ix, iy, x, y);
						brushPath.push_back(x);
						brushPath.push_back(y);
					}
					
				}
			}
		private:
			bool created = false;
			unsigned int vaoBrushPath;
			unsigned int vboBrushPath;
			bool isPainting = false, paintingMode = false;
			std::vector<float> brushPath;
			const int Max_Points = 2048;
			GLfloat g_vertex_buffer_data[8] = {
				-1.0f,1.0f,
				-1.0f,-1.0f,
				1.0f,1.0f,
				1.0f,-1.0f
			};
			void MapMouse(int ix, int iy, float& x, float &y)
			{
				//std::cout << ix << " " << iy << "\n";
				x = (float)ix / (float)600;//glutGet(GLUT_WINDOW_WIDTH); // map to 0 to 1
				//x = 2 * x - 1; // map to -1 to 1
				y = (float)iy / (float)600;//glutGet(GLUT_WINDOW_HEIGHT); // map to 0 to 1
				y = 1 - y;
				//y = 2 * y -1; // map to 1 to -1 (flip the window coordinates)
				//std::cout << x << " " << y << "\n";
			}

		};
	}
}