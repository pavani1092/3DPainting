#pragma once

#include "ICommand.h"
#include "OpenGL.h"

namespace Crawfis
{
	namespace Graphics
	{
		class SetPolygonModeCommand : public Collections::IGenericCommand
		{
		public:
			SetPolygonModeCommand(int mode = GL_FILL)
			{
				this->mode = mode;
			}
			virtual void Execute()
			{
				glPolygonMode(GL_FRONT_AND_BACK, mode);
			}
		private:
			int mode;
		};
	}
}