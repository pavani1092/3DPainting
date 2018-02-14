#pragma once

#include "ISceneNode.h"
#include "IVisitor.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Interfacew for all transforms.
		//   Extends the ISceneNode with many methods to influence the
		//   current coordinate system transformation. Also adds an
		//   Apply and Unapply methods used by the visitors to set the state
		//   of the graphics context.
		//
		class ITransformNode : public ISceneNode
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
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString() = 0;
		};
	}
}