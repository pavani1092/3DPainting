#pragma once

#include "IVisitor.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		class ISceneNode
		{
		public:
			virtual void Accept(IVisitor* visitor) = 0;
			virtual std::string ToString() = 0;
		};
	}
}