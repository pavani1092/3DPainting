#pragma once

#include "ITransformNode.h"
#include "IKeyboardHandler.h"
#include "IMouseHandler.h"
#include "OpenGL.h"
#include <iostream>

using namespace Crawfis::Controller;

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A composite ITransformNode used for moving a paint brush
		// Also supports the IKeyboardHandler and IMouseHandler interfaces.
		//
		class PaintController : public ITransformNode, public IKeyboardHandler, public IMouseHandler
		{
		public:
			//
			// Constructor. 
			//
			PaintController(std::string name, ISceneNode* subject) 
			{
				this->name = name;
			}
			//
			// Overrided from ISceneNode
			//
			virtual void Accept(IVisitor* visitor)
			{
				int error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
				visitor->Visit(this);
				error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
			}
			//
			// Traverse the child node.
			//
			void AcceptSubject(IVisitor* visitor)
			{
				rootNode->Accept(visitor);
			}
			// 
			// Apply the transform.
			// This is a no-op here, as the real transforms are in
			// the composite.
			//
			virtual void Apply() { }
			// 
			// Remove or undo the application of the transform.
			// This is a no-op here, as the real transforms are in
			// the composite.
			//
			virtual void Unapply() { }
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}
			//
			// Handle the main keyboard key presses. 
			// Called on both key down and key up.
			//
			virtual void KeyPress(unsigned char key, int x, int y)
			{
				switch(key)
				{
					case 'z':
						glutPostRedisplay();
						break;
					case 'Z':
						glutPostRedisplay();
						break;
				}
			}
			//
			// Handle the arrow keys and numeric keypad.
			//
			virtual void NumPadPress(int key, int x, int y)
			{
				switch(key)
				{
					case GLUT_KEY_LEFT:
						glutPostRedisplay();
						break;
					case GLUT_KEY_RIGHT:
						glutPostRedisplay();
						break;
					case GLUT_KEY_UP:
						glutPostRedisplay();
						break;
					case GLUT_KEY_DOWN:
						glutPostRedisplay();
						break;
				}
			}
			//
			// Handle any mouse button events, both press and release.
			//
			virtual void MouseEvent(int button, int state, int ix, int iy)
			{
				if( button == GLUT_LEFT_BUTTON)
				{
					if( state == GLUT_DOWN)
					{
						isPainting = true;
					}
					else
					{
						isPainting = false;
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
				if( isPainting )
				{
					float x, y;
					MapMouse(ix,iy,x,y);
					glutPostRedisplay();
				}
			}

		private:
			void MapMouse(int ix, int iy, float& x, float &y)
			{
				x = (float) ix / (float) windowWidth; // map to 0 to 1
				x = 2*x - 1; // map to -1 to 1
				y = (float) iy / (float) windowHeight; // map to 0 to 1
				y = 1 - 2*y; // map to 1 to -1 (flip the window coordinates)
			}

		private:
			std::string name;
			ITransformNode* rootNode;
			bool isPainting = false;
			int windowWidth, windowHeight;
		};
	}
}