#pragma once

#include "IDrawableNode.h"
#include "ModelManager.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IDrawableNode
		// Uses an indirection to draw a registered model.
		//
		class DrawableProxy : public IDrawableNode
		{
		public:
			//
			// Constructor.
			//   All names should be unique.
			//   The model name should refer to a registered model.
			//
			DrawableProxy(std::string name, std::string modelName)
			{
				this->name = name;
				this->modelName = modelName;
			}
			// 
			// Draw the model.
			//
			virtual void Draw()
			{
				ModelManager::Instance()->DrawModel(modelName);
			}
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}

		private:
			std::string name;
			std::string modelName;
		};
	}
}