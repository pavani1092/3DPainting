#pragma once

#include "OpenGL.h"
#include "IDrawable.h"

namespace Crawfis
{
	namespace Graphics 
	{
		class DrawableTeapot : public IDrawable
		{
		public:
			DrawableTeapot(bool wireframe = false) 
			{
				this->wireframe = wireframe;
				created = false;
				displayList = 0;
			}
			virtual void Draw()
			{
				InternalDraw();
			}
		private:
			void CreateTeapot()
			{
                // Create a new display list.
                created = true;
				displayList = glGenLists(1);
				glNewList(displayList, GL_COMPILE);
                if( wireframe )
					glutWireTeapot(1.0f);
                else
					glutSolidTeapot(1.0f);

				glEndList();
			}
			void InternalDraw()
			{
				if (!created)
				{
					CreateTeapot();
				}
				//
				// Actually draw the sphere
				//
				glCallList(displayList);
			}
		private:
			bool created;
			unsigned int displayList;
			bool wireframe;
			static const int minSubdivision = 10;
		};
	}
}