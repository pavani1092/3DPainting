#pragma once

#include <string>
#include "ILight.h"

namespace Crawfis
{
	namespace Graphics
	{
		class LightManager
		{
		public:
			static LightManager* Instance()
			{
				if (!created)
				{
					instance = new LightManager();
					created = true;
				}
				return instance;
			}
			ILight* GetLight(int lightIndex)
			{
				if (lightIndex < 0 || lightIndex >= maxLights)
					return 0;
				return lightSet[lightIndex];
			}
			void SetLight(int lightIndex, ILight* light)
			{
				if (lightIndex < 0 || lightIndex >= maxLights)
					return;
				lightSet[lightIndex] = light;
			}
			void EnableLight(int lightIndex)
			{
				if (lightIndex < 0 || lightIndex >= maxLights)
					return;
				lightEnabled[lightIndex] = true;
			}
			void DisableLight(int lightIndex)
			{
				if (lightIndex < 0 || lightIndex >= maxLights)
					return;
				lightEnabled[lightIndex] = false;
			}
		private:
			LightManager()
			{
				lightSet = new ILight*[maxLights];
				lightEnabled = new bool[maxLights];
				for (int i = 0; i < maxLights; i++)
				{
					lightSet[i] = 0;
					lightEnabled[i] = false;
				}
			}
		private:
			static bool created;
			static LightManager* instance;
			const int maxLights = 2;
			ILight** lightSet;
			bool* lightEnabled;
		};
	}
}
