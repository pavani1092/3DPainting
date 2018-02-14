#pragma once

#include "IShaderRoutine.h"
#include "FileUtility.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		class VertexRoutine : public IShaderRoutine
		{
		public:
			VertexRoutine(std::string fileName)
			{
				this->fileName = fileName;
				created = false;
				guid = 0;
			}

			//
			// Get the shader id (Guid).
			// If the routine has not been created or compiled,
			// perform that before returning the guid.
			//
			virtual unsigned int getGUID()
			{
				if( !created )
				{
					CreateRoutine();
				}
				return guid;
			}
		private:
			void CreateRoutine()
			{
				guid = glCreateShader(GL_VERTEX_SHADER);
				if( guid != 0 )
				{
					LoadSource();
					Compile();
					SetCompileLog();
					created = true;
				}
			}
			void LoadSource()
			{
				char* sourceCode = Crawfis::IO::FileUtility::File2CharArray(fileName.c_str());
				if (sourceCode == 0)
					throw "Error reading shader file.";
				glShaderSource(guid, 1, (const GLchar**)&sourceCode, 0);
			}
			void Compile()
			{
				glCompileShader(guid);
			}
			void SetCompileLog()
			{
				int maxLength;
				glGetShaderiv(guid, GL_INFO_LOG_LENGTH, &maxLength);
				char* compilerErrors = new char[maxLength];
				glGetShaderInfoLog(guid, maxLength, &maxLength, compilerErrors);
				compileLog.assign(compilerErrors);
			}
		private:
			unsigned int guid;
			bool created;
			std::string fileName;
			std::string compileLog;
		};
	}
}
