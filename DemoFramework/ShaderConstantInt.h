#pragma once

#include "IShaderConstant.h"
#include "Vector.h"

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of a IShaderConstant for 4-component vectors 
		//
		class ShaderConstantInt : public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			ShaderConstantInt(std::string constantName)
			{
				this->constantName = constantName;
			}
			void setValue(const int value)
			{
				this->value = value;
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
				constantLocation = glGetUniformLocation(shaderID, constantName.c_str());
				//std::cout << "loc for " << constantName << " " << constantLocation << std::endl;
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{
				std::cout << "const loc " << constantLocation << " value " << value << std::endl;
				if (constantLocation >= 0)
					glUniform1i(constantLocation, value);
			}

		private:
			std::string constantName;
			int constantLocation;
			int value;
		};
	}
}