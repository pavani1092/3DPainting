#pragma once

#include "ICommand.h"
#include "OpenGL.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics
	{
		class ClearColorCommand : public Collections::IGenericCommand
		{
		public:
			ClearColorCommand(Color& clearColor = Colors::Transparent)
			{
				this->clearColor = clearColor;
			}
			virtual void Execute()
			{
				glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a); 
				glClear(GL_COLOR_BUFFER_BIT);
			}
		private:
			Color clearColor;
		};
	}
}