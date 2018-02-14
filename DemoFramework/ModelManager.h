#pragma once

#include <string>
#include <map>
#include "IDrawable.h"
#include "MaterialManager.h"
#include "OpenGL.h"
#include <iostream>


namespace Crawfis
{
	namespace Graphics 
	{
		//
		// MaterialManager implements a Singleton design pattern for global
		// access and registration of materials.
		//
		class ModelManager
		{
		public:
			//
			// Get the one and only instance of the MaterialManager
			//
			static ModelManager* Instance()
			{
				if( !created)
				{
					instance = new ModelManager();
					created = true;
				}
				return instance;
			}
			//
			// Look-up a material registered by it's name and
			// enable it. If the material is not registered an
			// exception will be thrown.
			//
			void DrawModel(std::string name)
			{
				MaterialManager::Instance()->SetShader();
				IDrawable* drawable = drawableMap[name];
				drawable->Draw();
			}
			//
			// Register a new material with the system.
			// If the material was already registered, the name will
			// now be associated with the new material.
			//
			void RegisterModel(std::string name, IDrawable* drawable)
			{
				drawableMap[name] = drawable;
			}
		private:
			ModelManager()
			{
			}
		private:
			static bool created;
			static ModelManager* instance;
			std::map<std::string,IDrawable*> drawableMap;
		};
	}
}
