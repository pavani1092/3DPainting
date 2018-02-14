#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for a texture applicator. For fixed
		// functionality in OpenGL, these are the TexEnv calls. For shaders
		// this is the binding of a shader sampler to the hardware texture
		// unit slot.
		// For DirectX 10, this can encapsulate the Texture View (Shader View).
		//
		class ITextureApplicator
		{
			friend class TextureBindManager;
			//
			// Note that there is nothing publically callable. This 
			// object is not used directly in the rendering. It must
			// be attached to a TextureBinding and then an ITextureBindManager
			// will call the Apply and Unapply methods.
			//
		protected:
			//
			// Enable (configure) the texture unit.
			//
			virtual void Apply(int hardwareUnit) = 0;
			//
			// Disable the texture unit.
			//
			virtual void Unapply(int hardwareUnit) = 0;

		};
	}
}