#pragma once

#include "IVisitor.h"
#include "IDrawableNode.h"
#include "ITransformNode.h"
#include "IStateNode.h"
#include "GroupNode.h"
#include <string>
#include <iostream>

namespace Crawfis
{
	namespace Graphics
	{
		class PrintSceneVisitor : public IVisitor
		{
		public:
			virtual void Visit(IDrawableNode* drawable)
			{
				std::string string = drawable->ToString();
				std::cout << preLine << string << "\n";
			}
			virtual void Visit(ITransformNode* transform)
			{
				std::string string = transform->ToString();
				std::cout << preLine << string << "\n";
				std::string lastPreLine = preLine;
				preLine.append("   ");
				transform->AcceptSubject(this);
				preLine = lastPreLine;
				int error = glGetError();
				if (error != 0)
					std::cout << "sdsahd";
			}
			virtual void Visit(IStateNode* state)
			{
				std::string string = state->ToString();
				std::cout << preLine << string << "\n";
				std::string lastPreLine = preLine;
				preLine.append("   ");
				state->AcceptSubject(this);
				preLine = lastPreLine;
			}
			virtual void Visit(GroupNode* group)
			{
				std::string string = group->ToString();
				std::cout << preLine << string << "\n";
				std::string lastPreLine = preLine;
				preLine.append("   ");
				group->AcceptChildren(this);
				preLine = lastPreLine;
			}
		private:
			std::string preLine;
		};
	}
}