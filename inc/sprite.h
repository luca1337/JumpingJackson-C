#ifndef SPRITE_H
#define SPRITE_H

#include <glad.h>
#include <stdlib.h>
#include <vec.h>
#include <shader_program.h>

typedef struct sprite{
    GLuint vao;
    GLuint tex;
    float width;
    float height;
    vec2_t position;
    vec3_t color;
    shader_program_t shader_prg;
}sprite_t;

int sprite_create(sprite_t* sprite, float width, float height, const char* texture);
void sprite_draw_color(sprite_t* sprite, const vec3_t color);
void sprite_draw_texture(sprite_t* sprite);
void sprite_set_color(sprite_t* sprite, const vec3_t color);
void sprite_move(sprite_t* sprite, float x, float y);

#endif