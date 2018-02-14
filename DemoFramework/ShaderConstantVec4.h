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
		class ShaderConstantVec4 : public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			ShaderConstantVec4(std::string constantName)
			{
				this->constantName = constantName;
			}
			void setValue( const Crawfis::Math::Vector4f& value )
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
				constantLocation = glGetUniformLocation( shaderID, constantName.c_str() );
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{
				if (constantLocation >= 0) {
					//std::cout << "sending " <<value.x<<"  "<<value.y<<" "<<value.z<< std::endl;
					glUniform4f(constantLocation, value.x, value.y, value.z, value.w);
				}
			}

		private:
			std::string constantName;
			unsigned int constantLocation;
			Crawfis::Math::Vector4f value;
		};
	}
}