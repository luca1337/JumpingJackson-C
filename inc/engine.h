#ifndef ENGINE_H
#define ENGINE_H

#include <glad.h>
#include <gl_context.h>
#include <shader_utils.h>
#include <shader_program.h>
#include <dict.h>

typedef struct engine{
    GLuint base_color;
    GLuint texture;
    GLuint animation;
    aiv_dict_t* programs;
    gl_context_t context;
    char is_running;
    int error;
    GLuint cam_pos, cam_rot, cam_fov;
}engine_t;

int engine_create(engine_t* engine, unsigned width, unsigned height, const char* title, unsigned depth, unsigned major, unsigned minor, void (*post_hook_draw)(gl_context_t *context), void (*post_engine_setup)(engine_t* engine), void (*post_shader_setup)(engine_t* engine));
void engine_tick(engine_t* engine);
void engine_shut_down(engine_t* engine);

#endif