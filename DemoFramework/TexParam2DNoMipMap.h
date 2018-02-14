#pragma once

#include "ITextureParameters.h"
#include "OpenGL.h"

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// Set the filtering to the common mip-mapping case.
		//
		class TexParam2DNoMipMap : public ITextureParameters {
		public:
			//
			// Set the minification filter mode and the magnification mode.
			void Apply()
			{
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			}
			//
			// Since there is no data, make a single static instance.
			//
			static TexParam2DNoMipMap Instance;

		private:
			TexParam2DNoMipMap() {}
		};
	}
}