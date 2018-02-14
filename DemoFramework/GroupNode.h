#pragma once

#include <vector>
#include "ISceneNode.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// An ISceneNode that holds a collection of ISceneNodes.
		//
		class GroupNode : public ISceneNode
		{
		public:
			GroupNode(std::string name)
			{
				this->name = name;
			}
			//
			// This is part of the Visitor Design Pattern. The individual nodes accept a visitor
			// and then can call the visitor's overloaded visit method with the run-time type.
			//
			// For a group node, the visit knows we are at a group when we do the double dispatch
			// with the Visit(GroupNode*) call. The visitor can then call the AcceptChildren method
			// on a group. We will not make assumptions on what the visit wants to do at this point.
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
			// Visit each of the group's children.
			//
			void AcceptChildren(IVisitor* visitor)
			{
				std::vector<ISceneNode*>::iterator childrenIterator;
				for( childrenIterator = children.begin(); childrenIterator != children.end(); childrenIterator++ )
				{
					(*childrenIterator)->Accept(visitor);
				}
			}
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}
			//
			// Add an ISceneNode to the group.
			//
			void AddChild(ISceneNode* child)
			{
				if( child != 0)
				{
					children.push_back(child);
				}
			}
		private:
			std::vector<ISceneNode*> children;
			std::string name;
		};
	}
}