#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad.h>

typedef struct shader_program{
    GLuint position;
    GLuint rotation;
    GLuint scale;
    GLuint color;
    GLuint tex;

    GLuint sprites_per_row;
    GLuint sprites_per_col;
    GLuint x_offset;
    GLuint y_offset;

    GLuint camera_position;
    GLuint camera_rotation;
    GLuint camera_fov;
}shader_program_t;

#endif