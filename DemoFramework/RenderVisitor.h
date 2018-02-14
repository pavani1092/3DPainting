#pragma once

#include "IVisitor.h"
#include "IDrawableNode.h"
#include "ITransformNode.h"
#include "IStateNode.h"
#include "GroupNode.h"

namespace Crawfis
{
	namespace Graphics
	{
		class RenderVisitor : public IVisitor
		{
		public:
			virtual void Visit(IDrawableNode* drawable)
			{
				//std::cout << drawable->ToString() << std::endl;
				drawable->Draw();
				int error = glGetError();
				if (error != 0) {
					std::cout << drawable->ToString() << "drawable " << error << std::endl;
				}
			}
			virtual void Visit(ITransformNode* transform)
			{
				//std::cout << transform->ToString() << std::endl;
				int error = glGetError();
				if (error != 0) {
					std::cout << transform->ToString() << "before transform " << error << std::endl;
				}
				transform->Apply();
				transform->AcceptSubject(this);
				transform->Unapply();
				error = glGetError();
				if (error != 0) {
					std::cout << transform->ToString() << " transform " << error << std::endl;
				}
			}
			virtual void Visit(IStateNode* state)
			{
				//std::cout << state->ToString() << std::endl;
				state->Apply();
				state->AcceptSubject(this);
				state->Unapply();
				int error = glGetError();
				if (error != 0) {
					std::cout << state->ToString() << " state " << error << std::endl;
				}
			}
			virtual void Visit(GroupNode* group)
			{
				//std::cout << group->ToString() << std::endl;
				group->AcceptChildren(this);
				int error = glGetError();
				if (error != 0) {
					std::cout << group->ToString() << " group " << error << std::endl;
				}
			}
		};
	}
}