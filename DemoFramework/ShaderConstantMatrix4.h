#pragma once
#include "IShaderConstant.h"
#include "Matrix.h"
#include <string>

namespace Crawfis
{
	namespace Graphics
	{
		class ShaderConstantMatrix4 : public IShaderConstant
		{
		public:
			ShaderConstantMatrix4(std::string constantName);
			~ShaderConstantMatrix4();
			void setValue(const Crawfis::Math::Matrix4& value);

			// Inherited via IShaderConstant
			virtual void OnLink(unsigned int shaderID) override;
			virtual void OnShaderEnabled(unsigned int shaderID) override;

		private:
			std::string constantName;
			unsigned int constantLocation;
			Crawfis::Math::Matrix4 value;

		};
	}
}

