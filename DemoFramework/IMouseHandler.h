#pragma once

namespace Crawfis
{
	namespace Controller
	{
		class IMouseHandler
		{
		public:
			// This somewhat assumes GLUT or some other framework, as button is an int
			virtual void MouseEvent(int button, int state, int ix, int iy) = 0;
			virtual void MouseMoved(int ix, int iy) = 0;
		};
	}
}
