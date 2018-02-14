#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all raster operation settings
		//
		class IRasterOps
		{
		public:
			//
			// Set the raster opertations (depth testing, alpha testing, ...).
			// This is typically part of an IMaterial and should be called before an
			// IDrawable draws itself.
			//
			virtual void Enable() = 0;
			//
			// Reset the raster opertations (depth testing, alpha testing, ...). 
			// This is typically part of an IMaterial and should be called before an
			// IDrawable draws itself.
			// Depending on your framework, this could be a no-op with the assumption
			// that all materials set all raster states. If you want / need incremental
			// changes from a canonical setting, then you can use Disable.
			//
			virtual void Disable() = 0;
		};
	}
}