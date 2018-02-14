#pragma once

#include "OpenGL.h"

#include "ShaderProgram.h"
#include "ShaderConstantModelView.h"
#include "ShaderConstantProjection.h"
#include "ShaderConstantModelViewProj.h"
#include "ShaderConstantNormalMatrix.h"
#include "ShaderConstantCollection.h"
#include <string>

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of IShaderProgram.
		// This is an immutable class.
		//
		class ShaderProgramWithMatrices : public ShaderProgram
		{
		public:
			//
			// Constructor. A constructor for the simple case of a single vertex 
			// and a single fragment shader (no geometry shader).
			//
			ShaderProgramWithMatrices(VertexRoutine* vertexShader, FragmentRoutine* fragmentShader, IShaderConstant* shaderConstant = 0)
				: ShaderProgram(vertexShader, fragmentShader, 0)
			{
				setShaderConstant(shaderConstant);
			}
			//
			// Constructor. A constructor for the simple case of a single vertex, geometry and 
			// fragment shader.
			//
			ShaderProgramWithMatrices(VertexRoutine* vertexShader, GeometryRoutine* geometryShader, FragmentRoutine* fragmentShader)
				: ShaderProgram(vertexShader, geometryShader, fragmentShader)
			{
			}
			~ShaderProgramWithMatrices()
			{
				if (shaderConstants) delete shaderConstants;
			}
			//
			// Set any shader constants. shaderConstant can be a list of shader constants.
			//
			virtual void setShaderConstant(IShaderConstant* shaderConstant)
			{
				if (shaderConstants) delete shaderConstants;
				shaderConstants = new ShaderConstantCollection();
				if(shaderConstant != 0)
					shaderConstants->AddConstant(shaderConstant);
				AddMatrices();
			}

		protected:
			//
			// Enable the shader.
			//
			virtual void Enable()
			{
				if (!shaderConstants) 
					setShaderConstant(0);
				ShaderProgram::Enable();
			}

		private:
			void AddMatrices()
			{
				ShaderConstantModelView* modelViewConstant = new ShaderConstantModelView(modelViewName);
				ShaderConstantProjection* projectionConstant = new ShaderConstantProjection(projectionName);
				ShaderConstantModelViewProj* mvpConstant = new ShaderConstantModelViewProj(modelViewProjName);
				ShaderConstantNormal* normalConstant = new ShaderConstantNormal(normalName);
				shaderConstants->AddConstant(modelViewConstant);
				shaderConstants->AddConstant(projectionConstant);
				shaderConstants->AddConstant(mvpConstant);
				shaderConstants->AddConstant(normalConstant);
				ShaderProgram::setShaderConstant(shaderConstants);
			}
		private:
			std::string modelViewName = "modelViewMatrix";
			std::string projectionName = "projectionMatrix";
			std::string modelViewProjName = "modelViewProjectionMatrix";
			std::string normalName = "normalMatrix";
			ShaderConstantCollection* shaderConstants = 0;
		};
	}
}