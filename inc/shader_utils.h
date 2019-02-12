#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <stdlib.h>
#include <SDL.h>
#include <glad.h>

GLuint compile_shader(const char* vertex, const char* geometry, const char* fragment);

#endif