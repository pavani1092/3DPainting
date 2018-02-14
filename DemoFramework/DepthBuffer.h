#pragma once

#include "IDepthBuffer.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete class for render buffers or depth buffers.
		//
		class DepthBuffer : public IDepthBuffer
		{
		public:
			DepthBuffer(int width, int height, bool stencilSupport)
			{
				this->width = width;
				this->height = height;
				this->stencilSupport = stencilSupport;
				created = false;
			}
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
			virtual unsigned int GUID()
			{
				if (!created)
					CreateDepthBuffer();
				return guid;
			}

		private:
			void CreateDepthBuffer()
			{
				glGenRenderbuffers(1, &guid);
				glBindRenderbuffer(GL_RENDERBUFFER, guid);
				if (stencilSupport)
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
				else
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
				created = true;
			}

		private:
			bool created;
			int width;
			int height;
			bool stencilSupport;
			unsigned int guid;
		};
	}
}