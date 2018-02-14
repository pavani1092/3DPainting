#pragma once

#include "TextureData2DBase.h"
#include "OpenGL.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Create a new 2D Texture Data Object (OpenGL texture object) with either
		// no texel data (solid transparent black) or a specified solid color. This
		// is useful when combined with a FBO or a separate texture updater (e.g., 
		// roaming terrain tiles) where the texel data will be replaced.
		//
		class BlankTexture2D : public TextureData2DBase
		{
		public:
			BlankTexture2D(int width, int height, unsigned int internalFormat = GL_RGBA, bool addBorder = false)
			{
				setColor = false;
				this->width = width;
				this->height = height;
				this->internalFormat = internalFormat;
				this->addBorder = addBorder;
				CheckDimensions();
			}

			BlankTexture2D(int width, int height, Color& fillColor, unsigned int internalFormat = GL_RGBA, bool addBorder = false)
			{
				setColor = true;
				this->width = width;
				this->height = height;
				this->fillColor = fillColor;
				this->internalFormat = internalFormat;
				this->addBorder = addBorder;
				CheckDimensions();
			}

		protected:
			//
			// Override the OnCreated method call.
			// The texture guid has been created and the texture
			// has already been bound to a texture unit.
			//
			virtual void OnCreated()
			{
				GLenum dummyVal1 = GL_RGBA;
				GLenum dummyVal2 = GL_FLOAT;
				int newWidth = width;
				int newHeight = height;
				float* colorData = 0;

				if ( addBorder )
				{
					newWidth += 2;
					newHeight += 2;
				}

				if( setColor )
				{
					colorData = new float[4*newWidth*newHeight];
					int index = 0;
					for( int i=0; i < (newWidth*newHeight); i++ )
					{
						colorData[index++] = fillColor.r;
						colorData[index++] = fillColor.g;
						colorData[index++] = fillColor.b;
						colorData[index++] = fillColor.a;
					}
				}

				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, newWidth, newHeight, 0, dummyVal1, dummyVal2, colorData);

				if( colorData != 0 )
					delete colorData;
			}

		private:
			void CheckDimensions()
			{
				if( width <= 0 )
					throw "Width of texture must be greater than zero.";
				if( height <= 0 )
					throw "Height of texture must be greater than zero.";
				if( width > MAX_TEXTURE_SIZE )
					throw "Width of texture must be less than maximum size.";
				if( height > MAX_TEXTURE_SIZE )
					throw "Height of texture must be less than maximum size.";
			}

		private:
			int width, height;
			unsigned int internalFormat;
			bool addBorder;
			Color fillColor;
			bool setColor;
		};
	}
}