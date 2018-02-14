#pragma once

#include "ICommand.h"
#include "OpenGL.h"
#include "Color.h"
#include <string>

namespace Crawfis
{
	namespace Graphics
	{
		class ClearFrameCommand : public Collections::IGenericCommand
		{
		public:
			ClearFrameCommand(Color& clearColor = Colors::Transparent, float clearDepth = 1.0f)
			{
				this->clearColor = clearColor;
				this->clearDepth = clearDepth;
			}
			virtual void Execute()
			{
				if (!isCleared|| name == "UVScene"|| name == "uv") {
					//std::cout << "calling clear from " + name << std::endl;
					glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
					glClearDepthf(clearDepth);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					isCleared = true;
				}
				
			}
			void setName(std::string name) {
				this->name = name;
			}
		private:
			Color clearColor;
			float clearDepth;
			bool isCleared = false;
			std::string name;
		};
	}
}