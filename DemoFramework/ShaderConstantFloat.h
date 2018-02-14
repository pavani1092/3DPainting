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
		class ShaderConstantFloat : public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			ShaderConstantFloat(std::string constantName)
			{
				this->constantName = constantName;
			}
			void setValue(const float value)
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

				if (constantLocation >= 0)
					glUniform1f(constantLocation, value);

			}

		private:
			std::string constantName;
			int constantLocation;
			float value;
		};
	}
}