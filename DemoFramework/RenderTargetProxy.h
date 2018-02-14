#pragma once
#include "ISceneNode.h"
#include "IVisitor.h"
#include "StateNodeBase.h"
#include "RenderManager.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// State node which uses the RenderManager
		// to access concrete render targets through their string-
		// based name.
		//   Extends the ISceneNode with methods to enable and 
		//   disable a render target associated with this node.
		//
		class RenderTargetProxy : public StateNodeBase
		{
		public:
			//
			// Constructor. All sub-classes require a name and renderTargetName
			//   All names should be unique.
			//   All renderTargetName names should refer to a registered render target.
			//
			RenderTargetProxy(std::string name, std::string renderTargetName, ISceneNode* subject) 
				: StateNodeBase(name, subject)
			{
				std::cout << "registring " << renderTargetName << std::endl;
				this->renderTargetName = renderTargetName;
			}
			//
			// Enable the render target associated with this RenderTargetProxy.
			// Overriden from IStateNode.
			//
			virtual void Apply()
			{
				int error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
				RenderManager::Instance()->EnableRenderTarget(renderTargetName);
				error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
			}
			//
			// Disable the render target associated with this RenderTargetProxy.
			// Overriden from IStateNode.
			//
			virtual void Unapply()
			{
				RenderManager::Instance()->DisableRenderTarget(renderTargetName);
			}

		private:
			std::string renderTargetName;
		};
	}
}