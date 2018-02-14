#pragma once

namespace Crawfis
{
	namespace Graphics 
	{
		class IShaderConstant
		{
		public:
			virtual void OnLink(unsigned int shaderID) = 0;
			virtual void OnShaderEnabled(unsigned int shaderID) = 0;
		};
	}
}