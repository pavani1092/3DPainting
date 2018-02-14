#pragma once

#include "ISceneNode.h"
#include "IVisitor.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Abstract base class for all drawable scene graph nodes.
		//   Extends the ISceneNode with a Draw method 
		//
		class IDrawableNode : public ISceneNode
		{
		public:
			// 
			// Draw the object - This is abstract and needs to be
			// overridded in the concrete classes.
			//
			virtual void Draw() = 0;
			//
			// Overrided from ISceneNode
			//
			virtual void Accept(IVisitor* visitor)
			{
				visitor->Visit(this);
			}
		};
	}
}