#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all material or effects
		//
		class IMaterial
		{
		public:
			//
			// Enable the material. This should be called before an
			// IDrawable draws itself.
			//
			virtual void Enable() = 0;
			//
			// Disable the material. This should be called after an
			// IDrawable draws itself.
			//
			virtual void Disable() = 0;
		};
	}
}