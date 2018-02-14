#pragma once

#include "TextureData2DBase.h"
#include "OpenGL.h"
#include "DevIL.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Create a new 2D Texture Data Object (OpenGL texture object) from
		// the image data stored in the indicated file. Uses the DevIL library.
		//
		class TextureDataImage : public TextureData2DBase
		{
		public:
			TextureDataImage(int fileNumber, unsigned int internalFormat = GL_RGBA)
			{
				this->filename = getFileName(fileNumber);
				this->internalFormat = internalFormat;
			}
			TextureDataImage(std::string filename, unsigned int internalFormat = GL_RGBA)
			{
				this->filename = filename;
				this->internalFormat = internalFormat;
			}

		protected:
			std::string getFileName(int num) {
				switch (num) {
				case 1: return "..\\Media\\Textures\\tex1.png";
				case 2: return "..\\Media\\Textures\\tex2.png";
				case 3: return "..\\Media\\Textures\\tex3.png";
				case 4: return "..\\Media\\Textures\\tex4.png";
				default: return "..\\Media\\Textures\\tex5.jpg";
				}
			}
			//
			// Override the OnCreated method call.
			// The texture guid has been created and the texture
			// has already been bound to a texture unit.
			//
			virtual void OnCreated()
			{
				//guid = ::ilutGLLoadImage((char*)filename.c_str());
				::ilLoadImage( (char*)filename.c_str() );
				int imageWidth = ilGetInteger( IL_IMAGE_WIDTH );
				int imageHeight = ilGetInteger( IL_IMAGE_HEIGHT);
				int width = 2;
				for( ; width < imageWidth; width*=2 ) {}

				int height = 2;
				for( ; height < imageHeight; height*=2 ) {}

				if( width > height )
				{
					width = height;
				}
				else
				{
					height = width;
				}
				unsigned char* data = new unsigned char[4*width*height];
				::iluScale(width, height, 1);
				int origin = ilGetInteger(IL_IMAGE_ORIGIN);
				if (origin == IL_ORIGIN_LOWER_LEFT)
				{
					iluFlipImage();
				}
				::ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);
				gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width,
					height, GL_RGBA, GL_UNSIGNED_BYTE,
					data);
			}

		private:
			std::string filename;
			bool fileNameChanged;
			unsigned int internalFormat;
		};
	}
}