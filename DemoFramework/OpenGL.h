#pragma once

#define ILUT_USE_OPENGL

#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#ifdef MaskOpenGL
#define glActiveTexture ActiveTextureShouldNotBeUsed
#define glBindTexture BindTextureShouldNotBeUsed
#endif

#define MAX_TEXTURE_SIZE 4096