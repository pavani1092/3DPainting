#pragma once

#include "OpenGL.h"
#include "TextureBindManager.h"
#include "TextureBinding.h"
#define MAX_TEXTURE_UNITS 16

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A Singleton used to bind and unbind textures to the hardware.
		// Also contains a factory method to create and manage the bindings.
		//
		class TextureBindManagerOpenGL : public TextureBindManager
		{
		public:
			//
			// Get the concrete instance of the ITextureBindManager.
			//
			static void Init()
			{
				setInstance( new TextureBindManagerOpenGL() );
			}
			//
			// Create a TextureBinding associating the texture and the texture applicator.
			//
			virtual TextureBinding* CreateBinding(ITextureDataObject* texture, ITextureApplicator* textureApplicator)
			{
				TextureBinding* binding = CreateNewBinding(texture, textureApplicator);
				setIsBound(binding,false);
				setHardwareSlot(binding, -1);

				return binding;
			}
			//
			// Enable (bind) the texture. 
			//
			virtual void Bind(TextureBinding* binding)
			{
				// TODO: This is now allowed and can be changed
				if( getIsBound(binding) )
					throw "TextureBinding is already bound. Can not bind a TextureBinding more than once.";

				int unit = FindFreeTextureUnit();
				glActiveTexture( GL_TEXTURE0 + unit );
				//glBindTexture(GL_TEXTURE_2D, (*binding).GUID());
				boundUnits[unit] = binding;
				this->setHardwareSlot(binding, unit);
				this->setIsBound(binding, true);
				//
				// Now do the actual binding.
				//
				BindInternal(binding);
			}
			//
			// Disable (unbind) the texture.
			//
			virtual void Unbind(TextureBinding* binding)
			{
				int unit = this->getHardwareSlot(binding);
				boundUnits[unit] = 0;
				glBindTexture( GL_TEXTURE_2D, 0 );
				this->setHardwareSlot(binding, -1);
				this->setIsBound(binding, false);
				//
				// No do the actual unbinding
				//
				UnbindInternal(binding);
			}

		protected:
			//
			// Constructor. Not public.
			//
			TextureBindManagerOpenGL() 
			{
				for(int i=0; i < MAX_TEXTURE_UNITS; i++)
				{
					boundUnits[i] = 0;
				}
			}

		private:
			int FindFreeTextureUnit()
			{
				for(int i=0; i < MAX_TEXTURE_UNITS; i++)
				{
					if( boundUnits[i] == 0 )
					{
						return i;
					}
				}
				throw "Can not bind the texture binding, All texture units are currently bound.";
			}

		private:
			TextureBinding* boundUnits[MAX_TEXTURE_UNITS];
		};
	}
}
