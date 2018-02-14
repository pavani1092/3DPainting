#pragma once

#include "ITextureParameters.h"
#include "OpenGL.h"

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// Set the 2D texture's wrap modes.
		//
		class TexParam2DWrapped : public ITextureParameters {
		public:
			TexParam2DWrapped( GLenum wrapMode )
			{
				this->wrapMode = wrapMode;
			}
			//
			// Set both the s and t texture coordinate wrapping modes.
			//
			void Apply()
			{
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode );
			}
		private:
			GLenum wrapMode;
		};
	}
}