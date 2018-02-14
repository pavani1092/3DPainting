#pragma once

#include "ITextureDataObject.h"
#include "ITextureApplicator.h"
#include "IDepthBuffer.h"

namespace Crawfis
{
	namespace Graphics 
	{
		class TextureBinding;
		//
		// A Singleton used to bind and unbind textures to the hardware.
		// Also contains a factory method to create and manage the bindings.
		//
		class ITextureBindManager
		{
		public:
			//
			// Get the concrete instance of the ITextureBindManager.
			//
			static ITextureBindManager* Instance()
			{
				if (!created)
					throw "ITextureBindManager has not been initialized to a concrete instance.";
				return instance;
			}
			//
			// Create a TextureBinding associating the texture and the texture applicator.
			//
			virtual TextureBinding* CreateBinding(ITextureDataObject* texture, ITextureApplicator* textureApplicator) = 0;
			//
			// Enable (bind) the texture. 
			//
			virtual void Bind(TextureBinding* binding) = 0;
			//
			// Disable (unbind) the texture.
			//
			virtual void Unbind(TextureBinding* binding) = 0;

		protected:
			//
			// Constructor. Not public.
			//
			ITextureBindManager() {}
			//
			// Set the instance of the ITextureBindManager.
			//
			static void setInstance( ITextureBindManager* bindManager )
			{
				instance = bindManager;
				created = true;
			}
			//
			// Internal bind utility to do the actual binding. Derived classes can call this
			// from their bind method after they set up the hardware texture unit.
			//
			void BindInternal(TextureBinding* binding);
			//
			// Internal unbind utility to do the actual unbinding. Derived classes can call this
			// from their unbind method after they set up the hardware texture unit.
			//
			void UnbindInternal(TextureBinding* binding);
			//
			// Methods to allow derived classes to access and set the TextureBinding.
			//
			TextureBinding* CreateNewBinding(ITextureDataObject* texture, ITextureApplicator* textureApplicator);
			bool getIsBound( TextureBinding* binding);
			void setIsBound( TextureBinding* binding, bool isBound);
			int getHardwareSlot( TextureBinding* binding);
			void setHardwareSlot( TextureBinding* binding, int slot);
			int getGUID( ITextureDataObject* texture);
			int getGUID( IDepthBuffer* buffer);

		protected:
			static bool created;
			static ITextureBindManager* instance;
		};
	}
}
