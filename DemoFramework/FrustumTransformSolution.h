#pragma once

#include "TransformNodeBase.h"
#include "MatrixStack.h"

namespace Crawfis
{
	namespace Graphics
	{
		//
		// A concrete implementation of the ITransformNode.
		// This implementation simply mulitplies the frustum 
		// defined by the current projection transform.
		//
		// This class is immutable.
		//
		class FrustumTransformSolution : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			FrustumTransformSolution(std::string name, ISceneNode* subject,
				double left, double right, double bottom, double top, double zNear, double zFar)
				: TransformNodeBase(name, subject)
			{
				this->left = left;
				this->right = right;
				this->bottom = bottom;
				this->top = top;
				this->zNear = zNear;
				this->zFar = zFar;
			}
			// 
			// Apply the transform. This just sets the state of the Projection Matrix stack.
			//
			virtual void Apply()
			{
				Matrix4 projection = FrustumSolution(left, right, bottom, top, zNear, zFar);
				projection = MatrixStack::projectionStack.top() * projection;
				MatrixStack::projectionStack.push(projection);
			}
			// 
			// Remove or undo the application of the transform. 
			//
			virtual void Unapply()
			{
				MatrixStack::projectionStack.pop();
			}
			//
			// Overrrided from ITransformNode
			//
			virtual std::string ToString()
			{
				std::string name = this->TransformNodeBase::ToString();
				// TODO: add more information about this transform node
				//   to the string.
				return name;
			}
		private:
			Matrix4 FrustumSolution(float left, float right, float bottom, float top, float znear, float zfar)
			{
				float temp, temp2, temp3, temp4;
				temp = 2.0f * znear;
				temp2 = right - left;
				temp3 = top - bottom;
				temp4 = zfar - znear;
				Matrix4 matrix;
				matrix[0] = temp / temp2;
				matrix[1] = 0.0;
				matrix[2] = 0.0;
				matrix[3] = 0.0;
				matrix[4] = 0.0;
				matrix[5] = temp / temp3;
				matrix[6] = 0.0;
				matrix[7] = 0.0;
				matrix[8] = (right + left) / temp2;
				matrix[9] = (top + bottom) / temp3;
				matrix[10] = (-zfar - znear) / temp4;
				matrix[11] = -1.0;
				matrix[12] = 0.0;
				matrix[13] = 0.0;
				matrix[14] = (-temp * zfar) / temp4;
				matrix[15] = 0.0;
				return matrix;
			}
		private:
			double fieldOfView;
			int width, height;
			double left, right;
			double bottom, top;
			double zNear, zFar;
		};
	}
}