#pragma once

#include "ILight.h"
#include "Vector.h"
#include "Color.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		class PointLight : public ILight
		{
		public:
			PointLight(std::string name)
			{
				this->position[0] = 0;
				this->position[1] = 1;
				this->position[2] = 0;
				this->position[3] = 1;
				setColor(Color(1,1,1,1));
				this->name = name;
			}

			PointLight(std::string name, Crawfis::Math::Vector3 position)
			{
				this->position[0] = position.x;
				this->position[1] = position.y;
				this->position[2] = position.z;
				this->position[3] = 1;
				setColor(Color(1,1,1,1));
				this->name = name;
			}
			//
			// Get the light position.
			//
			virtual Crawfis::Math::Vector4 getPosition()
			{
				return Crawfis::Math::Vector4(position);
			}
			//
			// Set the light position.
			//
			void setPosition(Crawfis::Math::Vector3 position)
			{
				this->position[0] = position.x;
				this->position[1] = position.y;
				this->position[2] = position.z;
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
			float position[4];
			float color[4];
			std::string name;
		};
	}
}