#pragma once

#include <windows.h>

namespace Crawfis {
	namespace Graphics {
		class RenderState
		{
		public:
			static int FrameNumber() { return frameNumber; }
			static float FrameTime() { return frameTime; }
			static int FPS() { return fps; }
			static void UpdateState();
		private:
			static int frameNumber;
			static float frameTime;
			static int fps;
			static LARGE_INTEGER lastTime;
			static LARGE_INTEGER lastCheckpoint;
			static double scaleFactor;
		};
	}
}