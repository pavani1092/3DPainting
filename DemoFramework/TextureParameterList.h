#pragma once

#include "ITextureParameters.h"
#include "OpenGL.h"
#include <vector>

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// A collection of ITextureParams
		//
		class TextureParameterList : public ITextureParameters {
		public:
			//
			// Apply the list of texture parameters in order.
			//
			void Apply()
			{
				std::vector<ITextureParameters*>::iterator paramIterator;
				for( paramIterator = compositeTexParams.begin(); paramIterator != compositeTexParams.end(); paramIterator++ )
				{
					(*paramIterator)->Apply();
				}
			}
			//
			// Add texture parameters to the list.
			// Note, depending on the implementation, these may need to be set before the first
			// call to Apply().
			//
			void Add(ITextureParameters* texParams)
			{
				compositeTexParams.push_back(texParams);
			}

		private:
			std::vector<ITextureParameters*> compositeTexParams;
		};
	}
}