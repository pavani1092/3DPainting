#pragma once

#include "ITextureParameters.h"
#include<iostream>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all texture data objects
		//
		class ITextureDataObject
		{
			friend class TextureBindManager;
		public:
			//
			// Set and ITextureParameters to aid in the configuration.
			//
			virtual void setTextureParams(ITextureParameters* texParams) = 0;
			//
			// Note that there is nothing publically callable behavior. This 
			// object is not used directly in the rendering. It must
			// be attached to a TextureBinding and then an ITextureBindManager
			// will call the Enable and Disable methods.
			//
		public:
			//
			// Enable (bind) the texture. 
			//
			virtual void Enable() = 0;
			//
			// Disable (unbind) the texture.
			//
			virtual void Disable() = 0;
			//
			// Get the hardware ID for this texture.
			//
			virtual unsigned int GUID() = 0;

			void setName(std::string name) {
				tname = name;
			}

			std::string getName() {
				return tname;
			}
			std::string tname;
		};
	}
}