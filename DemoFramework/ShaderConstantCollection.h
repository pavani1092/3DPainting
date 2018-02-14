#pragma once

#include "IShaderConstant.h"
#include <vector>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of a IShaderConstant for 4-component vectors 
		//
		class ShaderConstantCollection : public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			ShaderConstantCollection()
			{
			}
			void AddConstant( IShaderConstant* constant )
			{
				constants.push_back(constant);
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
				std::vector<IShaderConstant*>::iterator constantIterator;
				for( constantIterator = constants.begin(); constantIterator < constants.end(); constantIterator++ )
				{
					(*constantIterator)->OnLink(shaderID);
				}
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{
				std::vector<IShaderConstant*>::iterator constantIterator;
				int i = 0;
				for( constantIterator = constants.begin(); constantIterator < constants.end(); constantIterator++ )
				{
					i++;
					(*constantIterator)->OnShaderEnabled(shaderID);
					int error = glGetError();
					if (error != 0) {
						std::cout << "const coll "<<i << std::endl;
					}
				}
				
			}

		private:
			std::vector<IShaderConstant*> constants;
		};
	}
}