#pragma once

#include "OpenGL.h"
#include "StateNodeBase.h"
#include <string>

namespace Crawfis
{
	namespace Graphics 
	{
		enum DrawModeType { SOLID, WIREFRAME, POINTS };
		//
		// Concrete implementation of IStateNode that sets
		// the OpenGL polygon mode (the draw mode).
		// This probably should have been 3 classes for readability.
		//
		class DrawModeNode : public StateNodeBase
		{
		public:
			//
			// Constructor. All sub-classes require a name.
			//
			DrawModeNode(std::string name, ISceneNode* subject, DrawModeType drawType = DrawModeType::SOLID)
				: StateNodeBase(name, subject)
			{
				this->drawType = drawType;
			}
			// 
			// Apply the Draw mode.
			//
			virtual void Apply()
			{
				switch (drawType)
				{
				case SOLID:
					glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
					break;
				case WIREFRAME:
					glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
					break;
				case POINTS:
					glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
					break;
				}
			}
			// 
			// Remove or undo the application of the draw mode.
			//
			virtual void Unapply()
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			}
			//
			// Set the Drawmode to the desired state on the next redraw.
			//
			void setDrawMode(DrawModeType drawType)
			{
				this->drawType = drawType;
			}

		private:
			DrawModeType drawType;
		};
	}
}