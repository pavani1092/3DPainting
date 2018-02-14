#include "RenderState.h"

namespace Crawfis {
	namespace Graphics {
		int RenderState::frameNumber = 0;
		float RenderState::frameTime = 0.0f;
		int RenderState::fps = 60;
		LARGE_INTEGER RenderState::lastTime;
		LARGE_INTEGER RenderState::lastCheckpoint;
		double RenderState::scaleFactor = 1.0;

		void RenderState::UpdateState()
		{
			if(frameNumber == 0)
			{
				QueryPerformanceCounter(&lastTime);
				LARGE_INTEGER countsPerSecond;
				QueryPerformanceFrequency(&countsPerSecond);
				scaleFactor = 1.0 / (double) countsPerSecond.QuadPart;
				lastCheckpoint = lastTime;
			}

			frameNumber++;

			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);
			frameTime = (float) (scaleFactor * (currentTime.QuadPart - lastTime.QuadPart));
			lastTime = currentTime;

			if( frameNumber % 100 == 0 )
			{
				fps = (int) (100.0 / (scaleFactor * (currentTime.QuadPart - lastCheckpoint.QuadPart)));
				lastCheckpoint = currentTime;
			}
		}
	}
}