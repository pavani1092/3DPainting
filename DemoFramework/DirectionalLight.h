#pragma once

#include "ILight.h"
#include "Vector.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics 
	{
		class DirectionalLight : public ILight
		{
		public:
			DirectionalLight(std::string name)
			{
				this->direction[0] = 0;
				this->direction[1] = 1;
				this->direction[2] = 0;
				this->direction[3] = 0;
				setColor(Color(1,1,1,1));
				this->name = name;
			}

			DirectionalLight(std::string name, Crawfis::Math::Vector3 direction)
			{
				direction.normalize();
				this->direction[0] = direction.x;
				this->direction[1] = direction.y;
				this->direction[2] = direction.z;
				this->direction[3] = 0;
				setColor(Color(1,1,1,1));
				this->name = name;
			}
			//
			// Get the light direction.
			//
			virtual Crawfis::Math::Vector4 getPosition()
			{
				return Crawfis::Math::Vector4(direction);
			}
			//
			// Set the light direction.
			//
			void setDirection(Crawfis::Math::Vector3 direction)
			{
				direction.normalize();
				this->direction[0] = direction.x;
				this->direction[1] = direction.y;
				this->direction[2] = direction.z;
			}
			//
			// Get the light color.
			//
			virtual Color getColor()
			{
				return Color(color);
			}
			//
			// Set the light color.
			//
			void setColor(Color color)
			{
				this->color[0] = color.r;
				this->color[1] = color.g;
				this->color[2] = color.b;
				this->color[3] = color.a;
			}

		private:
			float direction[4];
			float color[4];
			std::string name;
		};
	}
}