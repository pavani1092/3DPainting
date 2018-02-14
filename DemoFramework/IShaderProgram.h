#pragma once

#include "IShaderConstant.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all material or effects
		//
		class IShaderProgram
		{
		public:
			//
			// Enable the shader. 
			// This is typically part of an IMaterial and should 
			// only be called within an IMaterial to ensure texture
			// binding and uniform samplers stay consistent.
			//
			// TODO: Could not figure out a way to hide these (except for
			//       something similar to ITextureBindManager).
			//
			virtual void Enable() = 0;
			//
			// Disable the shader.
			// This is typically part of an IMaterial and should be called before an
			// IDrawable draws itself.
			// Depending on your framework, this could be a no-op with the assumption
			// that all materials set the current shader program. If you want / need incremental
			// changes from a canonical setting, then you can use Disable.
			//
			virtual void Disable() = 0;
			//
			// Add shader constant bindings.
			//
			virtual IShaderConstant* getShaderConstant() = 0;
			virtual void setShaderConstant(IShaderConstant* shaderConstant) = 0;
		};
	}
}