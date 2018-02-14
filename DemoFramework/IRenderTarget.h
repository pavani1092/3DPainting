#pragma once

#include "ICommand.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all render targets
		//
		class IRenderTarget
		{
		public:
			//
			// Enable the render target.
			//
			virtual void Enable() = 0;
			//
			// Disable the render target.
			//
			virtual void Disable() = 0;
			//
			// Set a command to be executed after the render target is enabled.
			//
			virtual void setEnableCommand(Crawfis::Collections::IGenericCommand* enableCommand) = 0;
			//
			// Set a command to be executed after the render target is enabled.
			//
			virtual void setDisableCommand(Crawfis::Collections::IGenericCommand* disableCommand) = 0;
		};
	}
}