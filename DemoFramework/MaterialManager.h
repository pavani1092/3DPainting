#pragma once

#include <string>
#include <map>
#include <stack>
#include "IMaterial.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// MaterialManager implements a Singleton design pattern for global
		// access and registration of materials.
		//
		class MaterialManager
		{
		public:
			//
			// Get the one and only instance of the MaterialManager
			//
			static MaterialManager* Instance()
			{
				if( !created)
				{
					instance = new MaterialManager();
					created = true;
				}
				return instance;
			}
			//
			// Look-up a material registered by it's name and
			// enable it. If the material is not registered an
			// exception will be thrown.
			//
			void EnableMaterial(std::string name)
			{
				IMaterial* material = materialMap[name];
				currentMaterial.push(material);
				//material->Enable();
			}
			//
			// Look-up a material registered by it's name and
			// disable it.If the material is not registered an
			// exception will be thrown.
			//
			void DisableMaterial(std::string name)
			{
				IMaterial* material = materialMap[name];
				currentMaterial.pop();
				material->Disable();
			}
			//
			// Register a new material with the system.
			// If the material was already registered, the name will
			// now be associated with the new material.
			//
			void RegisterMaterial(std::string name, IMaterial* material)
			{
				materialMap[name] = material;
			}
			void SetShader()
			{
				currentMaterial.top()->Enable();
			}
		private:
			MaterialManager()
			{
			}
		private:
			static bool created;
			static MaterialManager* instance;
			std::map<std::string,IMaterial*> materialMap;
			std::stack<IMaterial*> currentMaterial;
		};
	}
}
