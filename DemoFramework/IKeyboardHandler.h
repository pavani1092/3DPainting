#pragma once

namespace Crawfis
{
	namespace Controller
	{
		class IKeyboardHandler
		{
		public:
			virtual void KeyPress(unsigned char key, int x, int y) = 0;
			// This somewhat assumes GLUT or some other framework, as key is an int
			virtual void NumPadPress(int key, int x, int y) = 0;
		};
	}
}
