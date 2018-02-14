#pragma once

#include "ICommand.h"
#include "OpenGL.h"
#include "RenderState.h"

namespace Crawfis
{
	namespace Graphics
	{
		class SwapCommand : public Collections::IGenericCommand
		{
		public:
			SwapCommand(bool updateRenderState = false)
			{
				this->updateRenderState = updateRenderState;
			}
			virtual void Execute()
			{
				glutSwapBuffers();
				if( updateRenderState)
					RenderState::UpdateState();
			}
		private:
			bool updateRenderState;
		};
	}
}