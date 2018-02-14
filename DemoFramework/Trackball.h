#pragma once

#include "Vector.h"
#include "TransformMatrixNodeSolution.h"

using namespace Crawfis::Math;
using namespace Crawfis::Graphics;

namespace Crawfis
{
	namespace Controller
	{
		class Trackball
		{
		public:
			Trackball(TransformMatrixNodeSolution* transformNode)
			{
				this->transformNode = transformNode;
				interacting = false;
			}
			//
			// Trackball implements a gimble rotation where we think of the mouse movement
			//   as not planar, but grabbing and spinning a virtual sphere. Any mouse
			//   movements within the projected sphere are mapped to the sphere's surface
			//   and rotation happens along the great circle between any two mouse movements.
			//   Mouse movements outside the projected sphere spin the scene about the viewing
			//   axis.
			//
			void BeginManipulation(float x, float y)
			{
				if( transformNode != 0)
				{
					interacting = true;
					lastPoint = trackBallMapping( x, y );
				}
			}
			void EndManipulation(float x, float y)
			{
				interacting = false;
			}
			void ManipulateTo(float x, float y)
			{
				//
				// Check that we are suppose to be rotating. If not, return.
				//
				if (!interacting)
					return;

				// 
				// Map the movement of the mouse onto a virtual sphere.
				//
				Vector3 curPoint = trackBallMapping( x, y );
				//
				// Determine the direction and the velocity
				//
				Vector3 direction = curPoint - lastPoint;
				float velocity = direction.length();
				if( velocity > 0.0001f )
				{
					//
					// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
					//
					Vector3 rotAxis = lastPoint.cross(curPoint);
					//
					// The rotation angle would be the angle between lastPoint and curPoint.
					//   This could be calculated as the arcsin( rotAxis.Length() ), but we already
					//   have the distance between the two points and this works out quite well and
					//   smooth, without the additional costs.
					//
					float rotAngle = velocity;
					//
					// Trigger the rotate event (this will be changed to a modelview event)
					//
					transformNode->Rotate(rotAngle, rotAxis);
					//
					// Save the location of the current point for the next movement. 
					//
					lastPoint = curPoint;
				}
			}
		protected:
			Vector3 trackBallMapping(float x, float y)
			{
				//
				// Utility routine to calculate the 3D position of a 
				// projectd unit vector onto the xy-plane. Given any
				// point on the xy-plane, we can think of it as the projection
				// from a sphere down onto the plane. The inverse is what we
				// are after.
				//
				Vector3 v(x, y, 0.0f);
				float d = v.length();
				//
				// Angel's textbook also has this as: 
				//    v.z = sqrt( 1.0 - ((d < 1.0) ? d : 1.0) );
				//
				v.z = (float) cosf( (3.141527f / 2.0f) * ((d < 1.0f) ? d : 1.0f) );
				v.normalize();

				return v;
			}
		protected:
			Vector3 lastPoint;
			bool interacting;
			TransformMatrixNodeSolution* transformNode;
		};
	}
};