#pragma once

#include "OpenGL.h"

#include "SimpleShaderMaterial.h"
#include "IMaterial.h"
#include "DepthTestedRasterOps.h"
#include "ShaderProgram.h"
#include "IShaderConstant.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IMaterial.
		//   - Uses the Material properties.
		//   - Reads in a vertex and a fragment shader from two separate files
		//   - standard depth testing
		// Probably could have derived this from SimpleShaderMaterial.
		//
		class ShadedMaterial : public SimpleShaderMaterial
		{
		public:
			//
			// Constructor.
			//
			ShadedMaterial(IShaderProgram* shader) : SimpleShaderMaterial(shader)
			{
				this->setRasterOps(new DepthTestedRasterOps());
				ambient = Colors::Black;
				diffuse = Colors::White;
				specular = Colors::Black;
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getAmbientReflection() const
			{
				return Color(ambient);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setAmbientReflection(Color ambient)
			{
				this->ambient = ambient;
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getDiffuseReflection() const
			{
				return Color(diffuse);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setDiffuseReflection(Color diffuse)
			{
				this->diffuse = diffuse;
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getSpecularReflection() const
			{
				return Color(specular);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setSpecularReflection(Color specular)
			{
				this->specular = specular;
			}
			//
			// Get the shininess exponent
			//
			float getShininess() const
			{
				return shininess;
			}
			//
			// Set the shininess exponent
			//
			void setShininess(float shininess)
			{
				this->shininess = shininess;
			}

		private:
			Color ambient;
			Color diffuse;
			Color specular;
			float shininess;
		};
	}
}