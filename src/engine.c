#include <engine.h>

static void engine_setup(engine_t* engine)
{
    engine->base_color = compile_shader("shaders/vertex.glsl", NULL, "shaders/fragment_color.glsl");
    engine->texture = compile_shader("shaders/vertex.glsl", NULL, "shaders/fragment_texture.glsl");
    engine->animation = compile_shader("shaders/vertex.glsl", NULL, "shaders/fragment_animation.glsl");
}

int engine_create(engine_t* engine, unsigned width, unsigned height, const char* title, unsigned depth, unsigned major, unsigned minor, void (*post_hook_draw)(gl_context_t* context), void (*post_engine_setup)(engine_t* engine), void (*post_shader_setup)(engine_t* engine))
{
    memset(engine, 0, sizeof(engine_t));

    int error = gl_context_create(&engine->context, width, height, title, depth, major, minor, post_hook_draw);

    engine->is_running = engine->context.is_running;

    if(!post_engine_setup)
    {
        SDL_Log("setup hook was not defined by user, please bind this function in order to setup the engine.");
        error = -1;
        engine->error = error;
        goto end0;
    }

    gl_context_setup(&engine->context);

    engine_setup(engine);

    post_engine_setup(engine);

    if(!post_shader_setup)
        engine_setup(engine);
    else
        post_shader_setup(engine);

end0:
    return error;
}

void engine_shut_down(engine_t* engine)
{
    engine->is_running = 0;
    gl_context_destroy(&engine->context);
}

void engine_tick(engine_t* engine)
{
    if(engine->error == -1)
        return;

    while(engine->is_running)
    {
        gl_context_update(&engine->context);
    }
}