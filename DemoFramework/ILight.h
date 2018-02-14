#pragma once
#include "Vector.h"
#include "Color.h"

using namespace Crawfis::Math;

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all lights
		//
		class ILight
		{
		public:
			//
			// Properties
			//
			virtual Vector4 getPosition() = 0;
			virtual Color getColor() = 0;
		};
	}
}