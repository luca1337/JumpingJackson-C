#define SDL_MAIN_HANDLED

#include <engine.h>
#include <sprite.h>
#include <vec.h>
#include <map.h>

engine_t engine;

sprite_t sprite0;
texture_t tex0;

vec3_t col;

static void setup(engine_t* engine)
{
    texture_create(&tex0, "assets/textures/oc.png");

    col = vec3_init(1, 1, 0);

    sprite_create(&sprite0, 0.2, 0.2);
}

static void draw(gl_context_t* context)
{
    // draw objects here
    if(gl_get_key(context, SDL_SCANCODE_ESCAPE))
        engine_shut_down(&engine);

    if(gl_get_key(context, SDL_SCANCODE_W))
        sprite_move(&sprite0, 0, -100);

    if(gl_get_key(context, SDL_SCANCODE_S))
        sprite_move(&sprite0, 0, 100);

    if(gl_get_key(context, SDL_SCANCODE_A))
        sprite_move(&sprite0, -100, 0);

    if(gl_get_key(context, SDL_SCANCODE_D))
        sprite_move(&sprite0, 100, 0);

    // sprite_draw_color(&sprite0, col);

    sprite_draw_texture(&sprite0, &tex0);
}

int main(int argc, char** argv)
{
    engine_create(&engine, 1024, 768, "OpenGL 2D Engine", 32, 4, 6, draw, setup);
    engine_tick(&engine);

    return 0;
}