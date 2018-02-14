#pragma once

#include "IKeyboardHandler.h"
#include "IMouseHandler.h"
#include "DrawableRenderState.h"
#include "OpenGL.h"

using namespace Crawfis::Controller;

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A IDrawableNode to display the debug screen (RenderStateNode).
		// Could have also made this a switch node or used a switch node 
		// internally. Either way, it is a drawable node.
		//
		class DefaultController : public IDrawableNode, public IKeyboardHandler
		{
		public:
			//
			// Constructor. 
			//
			DefaultController(std::string name, int windowGUID)
			{
				this->name = name;
				this->windowGUID = windowGUID;
				this->renderStateNode = new DrawableRenderState("Default Overlay");
				showFPS = false;
			}
			//
			// The Draw command.
			//
			virtual void Draw()
			{
				if (showFPS)
					renderStateNode->Draw();
			}
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
				//
				// Misc. key controls.
				//
				switch(key)
				{
					// Typical quit command keys
					case 'Q':
					case 'q':
					case 'X':
					case 'x':
						glutDestroyWindow(windowGUID);
						exit(0);
						break;
					case 'f':
						showFPS = !showFPS;
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
			DrawableRenderState* renderStateNode;
			bool showFPS;
			std::string name;
			int windowGUID;
		};
	}
}