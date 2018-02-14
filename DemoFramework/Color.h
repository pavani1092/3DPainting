#pragma once

#include "Vector.h"

// TODO: This probably needs some additional functionality.
namespace Crawfis
{
	namespace Graphics 
	{
		// Choices: Inherit from vec4, typedef as a vec4, new class.
		// The first two perhaps allow operations we do not want on a color (cross product, etc.).
		// Should use an Adaptor pattern that contains a vec4.
		typedef Crawfis::Math::vec4<float> Color;
		class Colors
		{
			public:
				static Color White;
				static Color Black;
				static Color Transparent;
				static Color Scarlet;
				static Color Grey;
				static Color IndianRed;
				static Color Brown;
				static Color Red;
				static Color Yellow;
				static Color Blue;
		};
	}
}
