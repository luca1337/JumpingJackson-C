#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>

typedef struct texture{
    GLuint id;
    unsigned int width;
    unsigned int height;
}texture_t;

int texture_create(texture_t* texture, const char* file_name);

#endif