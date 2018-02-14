#pragma once

#include "ISceneNode.h"
#include "IVisitor.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Interface for all remaining state nodes.
		//   Adds a Apply and Unapply methods used by the visitors to set
		//   the state of the graphics context.
		// Design Note: Technically the ITransformNode and IMaterialNode
		//   classes are state change nodes. They are more common and I 
		//   wanted to separate them from this. Here we envision more
		//   esoteric or ad-hoc state changes (glPolygonMode, etc.).
		//
		class IStateNode : public ISceneNode
		{
		public:
			// 
			// Apply the transform - This is abstract and needs to be
			// overridded in the concrete classes.
			//
			virtual void Apply() = 0;
			// 
			// Remove or undo the application of the transform - This is abstract
			// and needs to be overridded in the concrete classes.
			//
			virtual void Unapply() = 0;
			//
			// Overrided from ISceneNode
			//
			virtual void Accept(IVisitor* visitor) = 0;
			//
			// Traverse the child node.
			//
			virtual void AcceptSubject(IVisitor* visitor) = 0;
		};
	}
}