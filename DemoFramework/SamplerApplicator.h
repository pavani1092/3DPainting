#pragma once

#include "ITextureApplicator.h"
#include "IShaderConstant.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// SamplerApplicator is both an ITextureApplicator and an IShaderConstant. 
		// It's main funciton is to associate a hardware texture unit with the 
		// sampler variable.
		//
		class SamplerApplicator : public ITextureApplicator, public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			SamplerApplicator(std::string samplerName)
			{
				this->samplerName = samplerName;
				hardwareUnit = -1;
			}
			//
			//
			// Note that there is no shader behavior that is publically callable. This 
			// object is not called directly in the rendering. As an ITextureApplicator,
			// it must be attached to a TextureBinding and then an ITextureBindManager
			// will call the Apply and Unapply methods. As an IShaderConstant, it will be
			// called by the 
			//
		protected:
			//
			// Enable (configure) the texture unit.
			// For shaders, we just need to remember which unit the
			// texture was bound to and set the uniform variable later.
			//
			virtual void ITextureApplicator::Apply(int hardwareUnit)
			{
				this->hardwareUnit = hardwareUnit;
			}
			//
			// Disable the texture unit. Nothing to do here.
			//
			virtual void ITextureApplicator::Unapply(int hardwareUnit)
			{
			}
			// Set-up any logic after a shader program has linked.
			// These should not be called by the user.
			//
			virtual void OnLink(unsigned int shaderID)
			{
				constantLocation = glGetUniformLocation( shaderID, samplerName.c_str() );
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{
				if (constantLocation >= 0) {
					glUniform1i(constantLocation, hardwareUnit);
				}
				int error = glGetError();
				if (error != 0) {
					std::cout << "const app " << std::endl;
				}
				
			}

		public:
			std::string samplerName;
			unsigned int hardwareUnit;
			unsigned int constantLocation;
		};
	}
}