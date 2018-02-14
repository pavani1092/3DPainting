#pragma once

#include "OpenGL.h"

#include "TransformNodeBase.h"
#include "Vector.h"
#include "MatrixStack.h"

using namespace Crawfis::Math;

namespace Crawfis
{
	namespace Graphics
	{
		//
		// A concrete implementation of the ITransformNode.
		// This implementation simply mulitplies the frustum 
		// defined by the current projection transform.
		//
		class PerspectiveTransformSolution : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			PerspectiveTransformSolution(std::string name, ISceneNode* subject)
				: TransformNodeBase(name, subject)
			{
				this->fieldOfView = 45;
				this->width = 100;
				this->height = 200;
				this->zNear = 0.5;
				this->zFar = 1000;
			}
			PerspectiveTransformSolution(std::string name, ISceneNode* subject,
				double fieldOfView, int width, int height, double zNear, double zFar)
				: TransformNodeBase(name, subject)
			{
				this->fieldOfView = fieldOfView;
				this->width = width;
				this->height = height;
				this->zNear = zNear;
				this->zFar = zFar;
			}
			void setWidth(int width)
			{
				this->width = width;
			}
			void setHeight(int height)
			{
				this->height = height;
			}
			// 
			// Apply the transform. 
			//
			virtual void Apply()
			{
				const double PI = 3.1415;
				float ymax, xmax;
				double aspectRatio = width / (double)height;
				ymax = zNear * tanf(fieldOfView * PI / 360.0f);
				xmax = ymax * aspectRatio;
				Matrix4 projection = FrustumSolution(-xmax, xmax, -ymax, ymax, zNear, zFar);
				Matrix4 transform = MatrixStack::projectionStack.top() * projection;
				MatrixStack::projectionStack.push(transform);
			}
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
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
			double zNear, zFar;
		};
	}
}