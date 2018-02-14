#pragma once

#include "TransformNodeBase.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A concrete implementation of the ITransformNode.
		//
		class ResetProjectionNodeSolution : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			ResetProjectionNodeSolution(std::string name, ISceneNode* subject) : TransformNodeBase(name, subject)
			{
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				Matrix4 identity;
				MatrixStack::projectionStack.push(identity);
			}
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
			//
			virtual void Unapply()
			{
				MatrixStack::projectionStack.pop();
			}
		};
	}
}