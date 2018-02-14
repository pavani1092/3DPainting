#pragma once
#include <stack>
#include "Matrix.h"

using namespace Crawfis::Math;

namespace Crawfis
{
	namespace Graphics
	{
		class MatrixStack {
		public:
			static void Init() {
				Matrix4 m;
				modelViewStack.push(m);
				projectionStack.push(m);
			}
			static std::stack<Matrix4> modelViewStack;
			static std::stack<Matrix4> projectionStack;
		};
	}
}

