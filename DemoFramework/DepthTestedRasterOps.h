#pragma once

#include "OpenGL.h"
#include "IRasterOps.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IRasterOps.
		//   - Standard depth testing.
		//   - no alpha testing
		//   - no stencil support
		//
		class DepthTestedRasterOps : public IRasterOps
		{
		public:
			//
			// Set the raster opertations (depth testing, alpha testing, ...).
			// This is typically part of an IMaterial and should be called before an
			// IDrawable draws itself.
			//
			virtual void Enable()
			{
				glEnable( GL_DEPTH_TEST );
			}
			//
			// Reset the raster opertations (depth testing, alpha testing, ...). 
			// This is typically part of an IMaterial and should be called before an
			// IDrawable draws itself.

			//
			virtual void Disable()
			{
				glDisable( GL_DEPTH_TEST );
			}
		};
	}
}
