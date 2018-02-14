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
		class ShaderConstantNormal : public IShaderConstant
		{
		public:
			ShaderConstantNormal(std::string constantName) : realConstant(constantName)
			{
			}

			~ShaderConstantNormal()
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
				Matrix4 normalMatrix = MatrixStack::modelViewStack.top();
				normalMatrix.inverse();
				normalMatrix.transpose();
				realConstant.setValue(normalMatrix);
				realConstant.OnShaderEnabled(shaderID);
				int error = glGetError();
				if (error != 0) {
					std::cout << "normal error " << std::endl;
				}
			}
		private:
			ShaderConstantMatrix4 realConstant;
		};
	}
}
