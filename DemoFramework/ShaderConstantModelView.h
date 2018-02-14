#pragma once
#include "IShaderConstant.h"
#include "ShaderConstantMatrix4.h"
#include "MatrixStack.h"
#include <string>

using namespace Crawfis::Math;
namespace Crawfis
{
	namespace Graphics
	{
		class ShaderConstantModelView : public IShaderConstant
		{
		public:
			ShaderConstantModelView(std::string constantName) : realConstant(constantName)
			{
			}

			~ShaderConstantModelView()
			{
			}
			//
			//
			// Note that there is no shader behavior that is publically callable. This 
			// object is not called directly in the rendering. As an IShaderConstant, 
			// it will be called by the ShaderProgram it is associated with
			//
		protected:
			//
			// Set-up any logic after a shader program has linked.
			// These should not be called by the user.
			//
			virtual void OnLink(unsigned int shaderID)
			{
				realConstant.OnLink(shaderID);
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{
				Matrix4 modelView = MatrixStack::modelViewStack.top();
				realConstant.setValue(modelView);
				realConstant.OnShaderEnabled(shaderID);
			}
		private:
			ShaderConstantMatrix4 realConstant;
		};
	}
}
