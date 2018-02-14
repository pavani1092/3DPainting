#pragma once

#include "StateNodeBase.h"
#include "ILight.h"
#include "LightManager.h"
#include <vector>
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IStateNode that allows for
		// a collection of ILights. Enables OpenGL lighting.
		//
		class LightSetNode : public StateNodeBase
		{
		public:
			//
			// Constructor. All sub-classes require a name.
			//
			LightSetNode(std::string name, ISceneNode* subject) : StateNodeBase(name, subject)
			{
			}
			// 
			// Turn on the lights.
			//
			virtual void Apply()
			{
				//std::vector<ILight*>::iterator lightIterator;
				//int lightSlot = 0;
				//for( lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++ )
				//{
				//	(*lightIterator)->Enable();
				//	lightSlot++;
				//}
			}
			// 
			// Turn off this lights.
			//
			virtual void Unapply()
			{
				//std::vector<ILight*>::iterator lightIterator;
				//int lightSlot = 0;
				//for( lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++ )
				//{
				//	(*lightIterator)->Disable();
				//	lightSlot++;
				//}
			}
			//
			// Add a light source to this set.
			//
			void AddLight(ILight* light)
			{
				lights.push_back(light);
			}

		private:
			std::vector<ILight*> lights;
		};
	}
}