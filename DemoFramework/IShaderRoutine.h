#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		class IShaderRoutine
		{
		public:
			//
			// Get the shader id (Guid).
			// If the routine has not been created or compiled,
			// perform that before returning the guid.
			//
			virtual unsigned int getGUID() = 0;
		};
	}
}
