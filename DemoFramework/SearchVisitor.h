#pragma once

#include "IVisitor.h"
#include "IDrawableNode.h"
#include "ITransformNode.h"
#include "IStateNode.h"
#include "GroupNode.h"
#include <string>

namespace Crawfis
{
	namespace Graphics
	{
		class SearchVisitor : public IVisitor
		{
		public:
			static ISceneNode* FindNode(std::string name, ISceneNode* scene)
			{
				SearchVisitor visitor(name);
				scene->Accept(&visitor);
				return visitor.getTarget();
			}
			SearchVisitor(std::string name)
			{
				this->searchName = name;
				targetNode = 0;
			}
			ISceneNode* getTarget() const
			{
				return targetNode;
			}
			virtual void Visit(IDrawableNode* drawable)
			{
				std::string name = drawable->ToString();
				if( name == searchName )
					targetNode = drawable;
			}
			virtual void Visit(ITransformNode* transform)
			{
				std::string name = transform->ToString();
				if( name == searchName )
					targetNode = transform;
				else
					transform->AcceptSubject(this);
			}
			virtual void Visit(IStateNode* state)
			{
				std::string name = state->ToString();
				if( name == searchName )
					targetNode = state;
				else
					state->AcceptSubject(this);
			}
			virtual void Visit(GroupNode* group)
			{
				std::string name = group->ToString();
				if( name == searchName )
					targetNode = group;
				else
					group->AcceptChildren(this);
			}
		private:
			std::string searchName;
			ISceneNode* targetNode;
		};
	}
}