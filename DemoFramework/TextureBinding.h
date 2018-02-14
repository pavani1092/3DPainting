#pragma once

#include "ITextureDataObject.h"
#include "ITextureApplicator.h"
#include "TextureBindManager.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Represents the data needed to associate a binding between
		// an ITextureDataObject, a TextureApplicator, and a hardware
		// texture slot.
		//
		class TextureBinding
		{
			friend TextureBindManager;
		public:
			//
			// Enable (bind) the texture. 
			//
			void Enable()
			{
				TextureBindManager::Instance()->Bind(this);
			}
			//
			// Disable (unbind) the texture.
			//
			void Disable()
			{
				TextureBindManager::Instance()->Unbind(this);
			}

			void setTexture(ITextureDataObject* texture) {
				this->texture = texture;

			 }
			unsigned int GUID() {
				return texture->GUID();
			}

		protected:
			//
			// Note that the constructor is protected. Use
			// TextureBindManager::Instance()->CreateBinding
			// to create a binding.
			//
			TextureBinding(ITextureDataObject* texture, ITextureApplicator* textureApplicator)
			{
				this->texture = texture;
				this->textureApplicator = textureApplicator;
			}

		protected:
			ITextureDataObject* texture;
			ITextureApplicator* textureApplicator;
			bool isBound;
			int hardwareSlot;
			void* bindData;
		};
	}
}