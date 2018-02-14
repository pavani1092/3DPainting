#pragma once

#include <string>
#include <map>
#include "IRenderTarget.h"
#include "OpenGL.h"
#include <iostream>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// RenderManager implements a Singleton design pattern for global
		// access and registration of render targets.
		//
		class RenderManager
		{
		public:
			//
			// Get the one and only instance of the RenderManager
			//
			static RenderManager* Instance()
			{
				if( !created)
				{
					instance = new RenderManager();
					created = true;
				}
				return instance;
			}
			//
			// Look-up a render target registered by it's name and
			// enable it. If the render target is not registered an
			// exception will be thrown.
			//
			void EnableRenderTarget(std::string name)
			{
				IRenderTarget* renderTarget = renderTargetMap[name];
				renderTarget->Enable();
				int error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
			}
			//
			// Look-up a render target registered by it's name and
			// disable it.If the render target is not registered an
			// exception will be thrown.
			//
			void DisableRenderTarget(std::string name)
			{
				IRenderTarget* renderTarget = renderTargetMap[name];
				renderTarget->Disable();
			}
			//
			// Register a new render target with the system.
			// If the render target was already registered, the name will
			// now be associated with the new render target.
			//
			void RegisterRenderTarget(std::string name, IRenderTarget* renderTarget)
			{
				renderTargetMap[name] = renderTarget;
			}
		private:
			RenderManager()
			{
			}
		private:
			static bool created;
			static RenderManager* instance;
			std::map<std::string,IRenderTarget*> renderTargetMap;
		};
	}
}
