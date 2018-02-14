#pragma once

#include "IStateNode.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Abstract base class for all remaining state nodes.
		//   Adds a Apply and Unapply methods used by the visitors to set
		//   the state of the graphics context.
		//
		class StateNodeBase : public IStateNode
		{
		public:
			//
			// Constructor. All sub-classes require a name.
			//
			StateNodeBase(std::string name, ISceneNode* subject)
			{
				this->name = name;
				this->subject = subject;
			}
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
			virtual void Accept(IVisitor* visitor)
			{
				int error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
				visitor->Visit(this);
				error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
			}
			//
			// Traverse the child node.
			//
			virtual void AcceptSubject(IVisitor* visitor)
			{
				subject->Accept(visitor);
			}
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}

		private:
			std::string name;
			ISceneNode* subject;
		};
	}
}