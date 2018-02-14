#pragma once

#include "ICommand.h"
#include "OpenGL.h"

namespace Crawfis
{
	namespace Graphics
	{
		class ClearDepthCommand : public Collections::IGenericCommand
		{
		public:
			ClearDepthCommand(float clearDepth = 1.0f)
			{
				this->clearDepth = clearDepth;
			}
			virtual void Execute()
			{
				glClearDepthf(clearDepth);
				glClear(GL_DEPTH_BUFFER_BIT);
			}
		private:
			float clearDepth;
		};
	}
}