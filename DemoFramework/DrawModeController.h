#pragma once

#include "IKeyboardHandler.h"
#include "IMouseHandler.h"
#include "DrawModeNode.h"
#include "OpenGL.h"
#include <string>

#include<iostream>
using namespace Crawfis::Controller;

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A IStateNode used to set and control the DrawMode
		// Supports the IKeyboardHandler interface with the keys:
		//    w -> Wireframe
		//    s -> Solid
		//    p -> Points
		//
		class DrawModeController : public IStateNode, public IKeyboardHandler
		{
		public:
			//
			// Constructor. 
			//
			DrawModeController(std::string name, ISceneNode* subject)
			{
				this->name = name;
				drawModeNode = new DrawModeNode("DrawMode", subject);
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
				drawModeNode->Accept(visitor);
			}
			// 
			// Apply the state.
			// This is a no-op here, as the real DrawNode is the subject.
			//
			virtual void Apply() { }
			// 
			// Remove or undo the state.
			// This is a no-op here.
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
					case 'w':
						drawModeNode->setDrawMode(DrawModeType::WIREFRAME);
						glutPostRedisplay();
						break;
					case 'p':
						drawModeNode->setDrawMode(DrawModeType::POINTS);
						glutPostRedisplay();
						break;
					case 's':
						drawModeNode->setDrawMode(DrawModeType::SOLID);
						glutPostRedisplay();
						break;
				}
			}
			//
			// Handle the arrow keys and numeric keypad.
			//
			virtual void NumPadPress(int key, int x, int y)
			{
			}

		private:
			DrawModeNode* drawModeNode;
			std::string name;
		};
	}
}