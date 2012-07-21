#ifndef CLIENT_VIEW_SHADER_LOADER_H
#define CLIENT_VIEW_SHADER_LOADER_H

#include <GL/glew.h>

void InitVideo();
GLuint LoadShaders(const char*, const char*, GLuint*, GLuint*);

#endif
