#include <gl_context.h>
#include <stdlib.h>
#include <string.h>
#include <glad.h>
#include <shader_utils.h>

int gl_context_create(gl_context_t* ctx, unsigned width, unsigned height, const char* title, unsigned depth, unsigned major_version, unsigned minor_version, void(*post_hook_draw)(gl_context_t* ctx))
{
    int ret = 0;

    if(!ctx->major_v) ctx->major_v = 3;
    if(!ctx->minor_v) ctx->major_v = 3;
    if(!ctx->depth) ctx->depth = 32;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_version);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        ret = -1;
        goto end1;
    }

    if(!title) title = "no title";

    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if(!window)
    {
        SDL_Log("Unable to initialize SDL Window: %s", SDL_GetError());
        ret = -1;
        goto end1;
    }

    ctx->window = window;

    // create opengl context wth major/minor version specified with setttribute
    ctx->sdlgl_context = SDL_GL_CreateContext(window);

    if(!ctx->sdlgl_context)
    {
        SDL_Log("%s", SDL_GetError());
        ret = -1;
        goto end2;
    }
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    int len = strlen(title);
    ctx->title = (char*)malloc(len + 1);
    strcpy(ctx->title, title);

    ctx->width = width;
    ctx->height = height;
    ctx->depth = depth;
    ctx->minor_v = minor_version;
    ctx->major_v = major_version;
    ctx->is_running = 1;
    ctx->post_hook_draw = post_hook_draw;
    ctx->key_state = SDL_GetKeyboardState(NULL);

    goto end0;

end2:
    SDL_DestroyWindow(ctx->window);
end1:
    SDL_Quit();
end0:
    return ret;
}

void gl_context_swap_buffers(gl_context_t* ctx)
{
    unsigned long long now = SDL_GetPerformanceCounter();
    ctx->delta_time = (float)(now - ctx->last_tick_time)/SDL_GetPerformanceFrequency();
    ctx->last_tick_time = now;

    SDL_GL_SwapWindow(ctx->window);
}

void gl_context_setup(gl_context_t* ctx)
{
    gl_clear_screen(0, 0, 0, 1);
}

void gl_context_update(gl_context_t* ctx)
{
    SDL_PumpEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    ctx->post_hook_draw(ctx);

    gl_context_swap_buffers(ctx);
}

void gl_clear_screen(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

uint8_t gl_get_key(gl_context_t* ctx, SDL_Scancode key_code)
{
    return ctx->key_state[key_code];
}

void gl_context_destroy(gl_context_t* ctx)
{
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}