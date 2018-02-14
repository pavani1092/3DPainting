#pragma once
#include "ISceneNode.h"
#include "IVisitor.h"
#include "StateNodeBase.h"
#include "MaterialManager.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Material node which uses the MaterialManager
		// to access concrete materials through their string-
		// based name.
		//   Extends the ISceneNode with methods to enable and 
		//   disable a material associated with this node.
		//
		class MaterialProxy : public StateNodeBase
		{
		public:
			//
			// Constructor. All sub-classes require a name and materialName
			//   All names should be unique.
			//   All material names should refer to a registered material.
			//
			MaterialProxy(std::string name, std::string materialName, ISceneNode* subject) 
				: StateNodeBase(name, subject)
			{
				this->materialName = materialName;
			}
			//
			// Enable the material associated with this MaterialProxy.
			// Overriden from IStateNode.
			//
			virtual void Apply()
			{
				MaterialManager::Instance()->EnableMaterial(materialName);
			}
			//
			// Disable the material associated with this MaterialProxy.
			// Overriden from IStateNode.
			//
			virtual void Unapply()
			{
				MaterialManager::Instance()->DisableMaterial(materialName);
			}

		private:
			std::string materialName;
		};
	}
}