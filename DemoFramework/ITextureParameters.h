#pragma once

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// OK. There are currently 3 (GL_TEXTURE_1D, etc.) times 15 possible configurations 
		// for OpenGL's texture parameter settings. Rather than have a monster configuration, 
		// this interface will support custom settings. Either complex special settings or
		// a Decorator Design pattern would be the best approach for setting these.
		//
		class ITextureParameters {
		public:
			//
			// Apply assumes the texture is currently bound and will apply any
			// texture configuration settings.
			//
			virtual void Apply() = 0;
		};
	}
}