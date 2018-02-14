#pragma once

#include "OpenGL.h"
#include "IRenderTarget.h"
#include "NullCommand.h"
#include "ITextureDataObject.h"
#include "IDepthBuffer.h"
#include <vector>
#include <string>

using namespace Crawfis::Collections;

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of IRenderTarget that sets
		// the current render target. Can also be used to set
		// the render target to the frame-buffer to allow for 
		// consistency.
		//
		class RenderTarget : public IRenderTarget
		{
		public:
			//
			// Constructor. All sub-classes require a name.
			//
			RenderTarget(ITextureDataObject* renderTextures, IDepthBuffer* depthBuffer = 0)
			{
				created = false;
				this->depthBuffer = depthBuffer;


				textures.push_back(renderTextures);


				guid = 0;
				enableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);
				disableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);

			}



			RenderTarget(std::vector<ITextureDataObject*>& renderTextures, IDepthBuffer* depthBuffer = 0)
			{
				created = false;
				this->depthBuffer = depthBuffer;
				std::vector<ITextureDataObject*>::iterator textureIterator;
				for (textureIterator = renderTextures.begin(); textureIterator != renderTextures.end(); textureIterator++)
				{
					textures.push_back(*textureIterator);
				}

				guid = 0;
				enableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);
				disableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);

			}
			//
			// Constructor for the default frame-buffer (the screen or window).
			//
			RenderTarget()
			{
				created = true;
				guid = 0;
				enableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);
				disableCommandarray.push_back(&Crawfis::Collections::NullCommand::Instance);

			}
			// 
			// Apply the Draw mode.
			//
			virtual void Enable()
			{
				if (!created)
					CreateFBO();
				glBindFramebuffer(GL_FRAMEBUFFER, guid);

				std::vector<IGenericCommand*>::iterator commandIterator;
				for (commandIterator = enableCommandarray.begin(); commandIterator != enableCommandarray.end(); commandIterator++)
				{
					(*commandIterator)->Execute();
				}



			}
			// 
			// Remove or undo the application of the draw mode.
			//
			virtual void Disable()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				std::vector<IGenericCommand*>::iterator commandIterator;
				for (commandIterator = disableCommandarray.begin(); commandIterator != disableCommandarray.end(); commandIterator++)
				{
					(*commandIterator)->Execute();
				}

			}
			//
			// Set a command to be executed after the render target is enabled.
			//
			void setEnableCommand(Crawfis::Collections::IGenericCommand* enableCommand)
			{
				this->enableCommandarray.push_back(enableCommand);
			}
			//
			// Set a command to be executed after the render target is enabled.
			//
			void setDisableCommand(Crawfis::Collections::IGenericCommand* disableCommand)
			{
				this->disableCommandarray.push_back(disableCommand);
			}

		private:
			void CreateFBO()
			{

				glGenFramebuffers(1, &guid);
				glBindFramebuffer(GL_FRAMEBUFFER, guid);
				int attachment = 0;
				std::vector<ITextureDataObject*>::iterator textureIterator;
				for (textureIterator = textures.begin(); textureIterator != textures.end(); textureIterator++)
				{
					//std::cout << "RT " << (*textureIterator)->getName()<<std::endl;
					unsigned int textureGuid = (*textureIterator)->GUID();
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment,
						GL_TEXTURE_2D, textureGuid, 0);
					attachment++;
				}

				if (depthBuffer != 0)
				{
					unsigned int depthGuid = depthBuffer->GUID();
					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthGuid);
				}
				int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
				if (status != GL_FRAMEBUFFER_COMPLETE)
					throw "Internal Error: The Frame Buffer Object (FBO) was not complete.";


				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				//created = true;

				//std::cout << "Drawn to FBO" << std::endl;
			}

		private:
			bool created;
			unsigned int guid;
			std::vector<IGenericCommand*> enableCommandarray;
			std::vector<IGenericCommand*> disableCommandarray;
			std::vector<ITextureDataObject*> textures;
			IDepthBuffer* depthBuffer;
		};
	}
}