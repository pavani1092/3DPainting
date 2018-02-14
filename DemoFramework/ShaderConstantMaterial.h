#pragma once

#include "OpenGL.h"
#include "IShaderConstant.h"
#include "Color.h"
#include <string>

using namespace Crawfis::Math;
namespace Crawfis
{
	namespace Graphics
	{
		struct Material
		{
			Color ambient;
			Color diffuse;
			Color specular;
			float shininess;
		};
		class ShaderConstantMaterial : public IShaderConstant
		{
		public:
			ShaderConstantMaterial(std::string constantName)
			{
				material.ambient = Colors::Black;
				material.diffuse = Colors::White;
				material.specular = Colors::White;
				material.shininess = 100;
				this->constantName = constantName;
			}
			~ShaderConstantMaterial() {}
			void setValue(ShadedMaterial* value)
			{
				material.ambient = value->getAmbientReflection();
				material.diffuse = value->getDiffuseReflection();
				material.specular = value->getSpecularReflection();
				material.shininess = value->getShininess();
				isDirty = true;
			}

			// Inherited via IShaderConstant
			virtual void OnLink(unsigned int shaderID) override
			{
				unsigned int error = glGetError();
				ambientLocation = glGetUniformLocation(shaderID, (constantName + "ambient").c_str());
				diffuseLocation = glGetUniformLocation(shaderID, (constantName+".diffuse").c_str());
				specularLocation = glGetUniformLocation(shaderID, (constantName+".specular").c_str());
				shininessLocation = glGetUniformLocation(shaderID, (constantName+".shininess").c_str());
				error = glGetError();
			}
			virtual void OnShaderEnabled(unsigned int shaderID) override
			{
				if (isDirty)
				{
					unsigned int error = glGetError();
					if (ambientLocation >= 0)
						glUniform4f(ambientLocation, material.ambient.x, material.ambient.y, material.ambient.z, material.ambient.w);
					if (diffuseLocation >= 0)
						glUniform4f(diffuseLocation, material.diffuse.x, material.diffuse.y, material.diffuse.z, material.diffuse.w);
					if (specularLocation >= 0)
						glUniform4f(specularLocation, material.specular.x, material.specular.y, material.specular.z, material.specular.w);
					if (shininessLocation >= 0)
						glUniform1f(shininessLocation, material.shininess);
					isDirty = false;
					error = glGetError();
					if (error != 0) {
						std::cout << "const mat " << std::endl;
					}
				}
				
			}

		private:
			std::string constantName;
			unsigned int ambientLocation;
			unsigned int diffuseLocation;
			unsigned int specularLocation;
			unsigned int shininessLocation;
			Material material;
			bool isDirty = true;
		};
	}
}