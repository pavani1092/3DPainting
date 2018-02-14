#pragma once
#include "ICommand.h"
#include "OpenGL.h"


namespace Crawfis
{
	namespace Graphics
	{
		class AdjustViewPortCommand : public Collections::IGenericCommand
		{
		public:
			AdjustViewPortCommand(int x, int y, int z, int w)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}
			virtual void Execute()
			{
				glViewport((GLint)x, (GLint)y, (GLsizei)z, (GLsizei)w);
				glScissor((GLint)x, (GLint)y, (GLsizei)z, (GLsizei)w);

			}
		private:

			int x, y, z, w;
		};
	}
}
