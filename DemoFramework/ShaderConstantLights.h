#pragma once

#include "OpenGL.h"
#include "IShaderConstant.h"
#include "Color.h"
#include "LightManager.h"
#include <string>

using namespace Crawfis::Math;
namespace Crawfis
{
	namespace Graphics
	{
		struct LightSource
		{
			Vector4 position;
			Color diffuse;
		};
		class ShaderConstantLights : public IShaderConstant
		{
		public:
			ShaderConstantLights()
			{
				positionName = "lightPositions";
				colorName = "lightColors";
			}
			~ShaderConstantLights() {}

			// Inherited via IShaderConstant
			virtual void OnLink(unsigned int shaderID) override
			{
				lightArrayLocation = glGetUniformLocation(shaderID, (positionName).c_str());
				lightArrayColorLocation = glGetUniformLocation(shaderID, (colorName).c_str());
			}
			virtual void OnShaderEnabled(unsigned int shaderID) override
			{
				float* lightPositions = new float[4*maxLights];
				float* lightColors = new float[4*maxLights];
				for (int i = 0; i < maxLights; i++)
				{
					ILight* light = LightManager::Instance()->GetLight(i);
					Vector4 position = light->getPosition();
					Color color = light->getColor();
					lightPositions[4 * i + 0] = position.x;
					lightPositions[4 * i + 1] = position.y;
					lightPositions[4 * i + 2] = position.z;
					lightPositions[4 * i + 3] = position.w;
					lightColors[4 * i + 0] = color.r;
					lightColors[4 * i + 1] = color.g;
					lightColors[4 * i + 2] = color.b;
					lightColors[4 * i + 3] = color.a;
				}
				if (lightArrayLocation >= 0)
					glUniform4fv(lightArrayLocation, maxLights, &lightPositions[0]);
				if (lightArrayColorLocation >= 0)
					glUniform4fv(lightArrayColorLocation, maxLights, &lightColors[0]);
				int error = glGetError();
				if (error != 0) {
					std::cout << "const light " << std::endl;
				}
			}

		private:
			std::string positionName;
			std::string colorName;
			unsigned int lightArrayLocation;
			unsigned int lightArrayColorLocation;
			const int maxLights = 2;
		};
	}
}