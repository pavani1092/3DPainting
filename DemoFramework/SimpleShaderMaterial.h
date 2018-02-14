#pragma once

#include "IMaterial.h"
#include "DepthTestedRasterOps.h"
#include "ShaderProgram.h"
#include "TextureBinding.h"
#include "Color.h"
#include <vector>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IMaterial.
		//   - Set all fragments to a solid color.
		//   - standard depth testing
		//
		class SimpleShaderMaterial : public IMaterial
		{
		public:
			//
			// Constructor.
			//
			SimpleShaderMaterial(IShaderProgram* shader)
			{
				this->shaderProgram = shader;
				this->rasterOps = new DepthTestedRasterOps();
				color = Colors::White;
			}
			//
			// Enable the material.
			//
			virtual void Enable()
			{
				std::vector<TextureBinding*>::iterator textureIterator;
				for( textureIterator = textureBindings.begin(); textureIterator != textureBindings.end(); textureIterator++ )
				{
					(*textureIterator)->Enable();
				}
				
				shaderProgram->Enable();
				rasterOps->Enable();
			}
			//
			// Disable the material. This will be a no-op for our system, since
			// we will require these to be set at the beginning of every material
			// when it is enabled.
			//
			virtual void Disable()
			{
				std::vector<TextureBinding*>::iterator textureIterator;
				for( textureIterator = textureBindings.begin(); textureIterator != textureBindings.end(); textureIterator++ )
				{
					(*textureIterator)->Disable();
				}
				shaderProgram->Disable();
				rasterOps->Disable();
			}
			//
			// Get the color.
			//
			Color getColor() const
			{
				return Color(color);
			}
			//
			// Set the color.
			//
			void setColor(Color color)
			{
				this->color = color;
			}
			void setShaderConstant(IShaderConstant* shaderConstant)
			{
				shaderProgram->setShaderConstant(shaderConstant);
			}
			IShaderConstant* getShaderConstant()
			{
				return shaderProgram->getShaderConstant();
			}
			void AddTexture(TextureBinding* binding)
			{
				textureBindings.push_back(binding);
			}
			//
			// Set the raster Ops
			//
			void setRasterOps(IRasterOps* rasterOps)
			{
				this->rasterOps = rasterOps;
			}

		private:
			IRasterOps* rasterOps;
			IShaderProgram* shaderProgram;
			std::vector<TextureBinding*> textureBindings;
			Color color;
		};
	}
}