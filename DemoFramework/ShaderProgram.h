#pragma once

#include "OpenGL.h"

#include "IShaderProgram.h"
#include "VertexRoutine.h"
#include "GeometryRoutine.h"
#include "FragmentRoutine.h"
#include "IShaderConstant.h"
#include <vector>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IShaderProgram.
		// This is an immutable class.
		//
		class ShaderProgram : public IShaderProgram
		{
		public:
			//
			// Constructor. A constructor for a ShaderProgram that uses the old
			// OpenGL Fixed Functional Pipeline model.
			//
			ShaderProgram()
			{
				guid = 0;
				// Set created to true, since we have a fixed-function pipeline.
				created = true;
				// Set the shaderConstant to null.
				shaderConstant = 0;
			}
			//
			// Constructor. A constructor for the simple case of a single vertex 
			// and a single fragment shader (no geometry shader).
			//
			ShaderProgram( VertexRoutine* vertexShader, FragmentRoutine* fragmentShader, IShaderConstant* shaderConstant = 0)
			{
				vertexRoutines.push_back(vertexShader);
				fragmentRoutines.push_back(fragmentShader);

				guid = 0;
				this->shaderConstant = shaderConstant;
				created = false;
			}
			//
			// Constructor. A constructor for the simple case of a single vertex, geometry and 
			// fragment shader.
			//
			ShaderProgram( VertexRoutine* vertexShader, GeometryRoutine* geometryShader, FragmentRoutine* fragmentShader)
			{
				vertexRoutines.push_back(vertexShader);
				geometryRoutines.push_back(geometryShader);
				fragmentRoutines.push_back(fragmentShader);

				created = false;
			}
			//
			// Set any shader constants. shaderConstant can be a list of shader constants.
			//
			virtual void setShaderConstant(IShaderConstant* shaderConstant)
			{
				this->shaderConstant = shaderConstant;
			}
			//
			// Return the shader constants.
			//
			virtual IShaderConstant* getShaderConstant()
			{
				return this->shaderConstant;
			}

		protected:
			//
			// Enable the shader.
			//
			virtual void Enable()
			{
				if( !created )
				{
					CreateProgram();
				}
				int error = glGetError();
				if (error != 0) {
					std::cout << "sdhgsja " << std::endl;
				}
				glUseProgram( guid );
				if( shaderConstant != 0 )
					shaderConstant->OnShaderEnabled(guid);
				error = glGetError();
				if (error != 0) {
					std::cout << "sdhgsja 222 " << std::endl;
				}
			}
			//
			// Disable the shader. This will be a no-op for our system, since
			// we will require these to be set at the beginning of every material
			// when it is enabled.
			//
			virtual void Disable()
			{
			}

		private:
			void CreateProgram()
			{
				guid = glCreateProgram();
				std::cout << "created prg with id " << guid << std::endl;
				AttachShaders(vertexRoutines);
				AttachShaders(fragmentRoutines);
				AttachShaders(geometryRoutines);
				Link();
				created = true;
			}

			void AttachShaders(std::vector<IShaderRoutine*> shaders)
			{
				std::vector<IShaderRoutine*>::iterator shaderIterator;
				for( shaderIterator = shaders.begin(); shaderIterator != shaders.end(); shaderIterator++ )
				{
					unsigned int shaderGuid = (*shaderIterator)->getGUID();
					glAttachShader(guid, shaderGuid);
				}

			}

			void Link()
			{
				glLinkProgram(guid);
				std::cout << "linking program " << guid << std::endl;
				if( shaderConstant != 0 )
					shaderConstant->OnLink(guid);
				SetLinkLog();
			}
			void SetLinkLog()
			{
				int maxLength;
				glGetProgramiv(guid, GL_INFO_LOG_LENGTH, &maxLength);
				char* linkErrors = new char[maxLength];
				glGetProgramInfoLog(guid, maxLength, &maxLength, linkErrors);
				if (maxLength > 0) {
					std::cout << "****************program******************" << std::endl;
					std::cout << linkErrors << std::endl;
				}
				linkLog.assign(linkErrors);
			}

		private:
			std::vector<IShaderRoutine*> vertexRoutines;
			std::vector<IShaderRoutine*> fragmentRoutines;
			std::vector<IShaderRoutine*> geometryRoutines;
			IShaderConstant* shaderConstant;
			unsigned int guid;
			bool created;
			std::string linkLog;
		};
	}
}