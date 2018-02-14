#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Abstract base class for all drawables.
		//
		class IDrawable
		{
		public:
			// 
			// Draw the object - This is abstract and needs to be
			// overridded in the concrete classes.
			//
			virtual void Draw() = 0;
		};
	}
}