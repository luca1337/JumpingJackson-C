#define SDL_MAIN_HANDLED

#include <engine.h>
#include <sprite.h>
#include <vec.h>

sprite_t sprite0;
sprite_t sprite1;
sprite_t sprite2;

engine_t engine;

vec3_t col;
vec3_t col2;

static void setup(engine_t* engine)
{
    col = vec3_init(1, 0, 1);
    col2 = vec3_init(1, 1, 1);

    sprite_create(&sprite0, 0.2, 0.2, "wall.jpg");

    // sprite_create(&sprite1, 0.1, 0.1);
}

static void draw(gl_context_t* context)
{
    // draw objects here
    if(gl_get_key(context, SDL_SCANCODE_ESCAPE))
        engine_shut_down(&engine);

    if(gl_get_key(context, SDL_SCANCODE_W))
        sprite_move(&sprite0, 0, 1);

    if(gl_get_key(context, SDL_SCANCODE_S))
        sprite_move(&sprite0, 0, -1);

    if(gl_get_key(context, SDL_SCANCODE_A))
        sprite_move(&sprite0, -1, 0);

    if(gl_get_key(context, SDL_SCANCODE_D))
        sprite_move(&sprite0, 1, 0);

    sprite_draw_texture(&sprite0);

    // sprite_draw_color(&sprite1, col2);

    // vec2_t end = vec2_sub(sprite0.position, sprite1.position);

    // sprite_move(&sprite1, end.x, end.y);
}

int main(int argc, char** argv)
{
    engine_create(&engine, 800, 600, "OpenGL 2D Engine", 32, 4, 6, draw, setup);
    engine_tick(&engine);

    return 0;
}