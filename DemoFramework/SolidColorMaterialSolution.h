#pragma once

#include "OpenGL.h"

#include "IMaterial.h"
#include "DepthTestedRasterOps.h"
#include "ShaderConstantVec4.h"
#include "ShaderProgramWithMatrices.h"
#include "Color.h"
#include <string>

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of IMaterial.
		//   - Set all fragments to a solid color.
		//   - standard depth testing
		// Old - Delete
		//
		class SolidColorMaterialSolution : public IMaterial
		{
		public:
			//
			// Constructor.
			//
			SolidColorMaterialSolution(Color color)
			{
				this->color = color;
				VertexRoutine* vertexRoutine = new VertexRoutine(vertexFile);
				FragmentRoutine* fragmentRoutine = new FragmentRoutine(fragmentFile);
				ShaderConstantVec4* colorConstant = new ShaderConstantVec4("defaultColor");
				colorConstant->setValue(color);
				this->shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine, colorConstant);
				this->rasterOps = new DepthTestedRasterOps();
			}
			//
			// Enable the material.
			//
			virtual void Enable()
			{
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
			}
		private:
			IRasterOps* rasterOps;
			IShaderProgram* shaderProgram;
			Color color;
			std::string vertexFile = "..\\Media\\Shaders\\SolidColorSolution.vert";
			std::string fragmentFile = "..\\Media\\Shaders\\SolidColorSolution.frag";
		};
	}
}