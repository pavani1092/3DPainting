#pragma once

#include "ITextureParameters.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for render buffers or depth buffers.
		//
		class IDepthBuffer
		{
			friend class ITextureBindManager;
		public:
			//
			// Note that there is nothing publically callable behavior. This 
			// object is not used directly in the rendering. It must
			// be attached to a TextureBinding and then an ITextureBindManager
			// will call the Enable and Disable methods.
			//
		public:
			//
			// Get the hardware ID for this texture.
			//
			virtual unsigned int GUID() = 0;
		};
	}
}