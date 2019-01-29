#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <stdint.h>
#include <SDL.h>

typedef struct gl_context{
    unsigned width;
    unsigned height;
    int major_v;
    int minor_v;
    char* title;
    int depth;
    char is_running;
    int aspect_ratio;
    void* window;
    SDL_GLContext sdlgl_context;
    float delta_time;
    unsigned long long last_tick_time;
    const uint8_t* key_state;
    void(*post_hook_draw)(struct gl_context*);
}gl_context_t;

int gl_context_create(gl_context_t* ctx, unsigned width, unsigned height, const char* title, unsigned depth, unsigned major_version, unsigned minor_version, void(*post_hook_draw)(gl_context_t* ctx));
void gl_context_swap_buffers(gl_context_t* ctx);
void gl_context_update(gl_context_t* ctx);
void gl_context_setup(gl_context_t* ctx);
uint8_t gl_get_key(gl_context_t* ctx, SDL_Scancode key_code);
void gl_clear_screen(float r, float g, float b, float a);
void gl_context_destroy(gl_context_t* ctx);

#endif