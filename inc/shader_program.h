#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad.h>

typedef struct shader_program{
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint draw_mode;

    GLuint width;
    GLuint height;
    GLuint color;
    GLuint tex;

    GLuint camera_position;
    GLuint camera_rotation;
    GLuint camera_fov;
}shader_program_t;

#endif