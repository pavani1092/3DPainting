#pragma once

#include "ITextureDataObject.h"
#include "ITextureParameters.h"
#include "OpenGL.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Abstract base class for 2D Textures. Override the OnCreated to 
		// set the format, width, height, etc. and load any initial texel data.
		//
		class TextureData2DBase : public ITextureDataObject
		{
		public:
			//
			// Destructor
			//
			~TextureData2DBase()
			{
				if( created )
				{
					glDeleteTextures(1, &guid);
					created = false;
					guid = -1;
				}
			}
			//
			// Set the ITextureParams.
			//
			void setTextureParams(ITextureParameters* texParams)
			{
				this->texParams= texParams;
			}

		protected:
			//
			// Constructor. Not public as this is an abstract class.
			//
			TextureData2DBase()
			{
				created = false;
				guid = -1;
				texParams = 0;
			}
			//
			// Enable the texture.
			// Overriden from ITexture.
			// Note: Would like this to be sealed. It should not be overriden.
			//
			virtual void Enable()
			{
				if( !created )
					CreateTexture();

				glBindTexture( GL_TEXTURE_2D, guid );
			}

			virtual void reset() {
				if (created)
				{
					glDeleteTextures(1, &guid);
					created = false;
					guid = -1;
				}
			}
			//
			// Disable the texture.
			// Overriden from ITexture.
			// Note: Would like this to be sealed. It should not be overriden.
			//
			virtual void Disable()
			{
				glBindTexture( GL_TEXTURE_2D, 0 );
			}
			//
			// Get the hardware ID for this texture.
			//
			virtual unsigned int GUID()
			{
				if( !created )
					throw "Can not get the GUID until the texture is created (Enabled).";
				// Note: This following line would have a serious side-effect if the user
				//     has a different texture currently bound to the current active 
				//     texture unit. Hence we do not do this.
				//CreateTexture();

				return guid;
			}
			//
			// This is an abstract method where the texture can be defined and any 
			// image data can be loaded. The basic call to glTexImage2D or an equivalent
			// should be called within this method.
			//
			virtual void OnCreated() = 0;

		private:
			virtual void CreateTexture()
			{
				//
				// Generate a hardware texture ID (guid) for the texture object
				// and bind it to the currently active.
				//
				glGenTextures(1, &guid );
				glBindTexture( GL_TEXTURE_2D, guid );
				created = true;
				//
				// Set the texture parameters.
				//
				if( texParams != 0 )
					texParams->Apply();
				//
				// Call the abstract OnCreated method to let the derived class
				// format and initialize the texture.
				//
				OnCreated();
				//
				// Unbind the texture. This is not needed as CreateTexture is/should only
				// be called from the Enable method. It does not hurt (only called once at
				// creation), so we will leave it for future safety.
				//
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

		protected:
			unsigned int guid;
			ITextureParameters* texParams;

		private:
			bool created;
		};
	}
}