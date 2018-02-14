#pragma once

namespace Crawfis
{
	namespace Graphics
	{
		class IDrawableNode;
		class ITransformNode;
		class IStateNode;
		class GroupNode;

		class IVisitor
		{
		public:
			virtual void Visit(IDrawableNode* drawable) = 0;
			virtual void Visit(ITransformNode* transform) = 0;
			virtual void Visit(IStateNode* state) = 0;
			virtual void Visit(GroupNode* group) = 0;
		};
	}
}