#define SDL_MAIN_HANDLED

#include <engine.h>
#include <sprite.h>
#include <vec.h>
#include <map.h>

sprite_t sprite0;
sprite_t sprite1;
sprite_t sprite2;

engine_t engine;

vec3_t col;
vec3_t col2;

map_t map0;

texture_t tex0;

const char* textures[] = {
    "wall.jpg",
    "lava.png",
    "wter.jpg"
};

int cells[5*5] = {
    1,0,1,0,2,
    0,1,2,1,0,
    2,0,1,0,0,
    2,1,1,2,0,
    0,1,1,2,2
};

static void setup(engine_t* engine)
{
    texture_create(&tex0, "wter.jpg");

    col = vec3_init(1, 1, 0);

    sprite_create(&sprite0, 0.2, 0.2);

    sprite_create(&sprite1, 0.2, 0.2);

    sprite_set_position(&sprite1, 50, 50);

    // map_create(&map0, 5, 5, cells, textures);
}

static void draw(gl_context_t* context)
{
    // draw objects here
    if(gl_get_key(context, SDL_SCANCODE_ESCAPE))
        engine_shut_down(&engine);

    if(gl_get_key(context, SDL_SCANCODE_W))
        sprite_move(&sprite1, 0, -100);

    if(gl_get_key(context, SDL_SCANCODE_S))
        sprite_move(&sprite1, 0, 100);

    if(gl_get_key(context, SDL_SCANCODE_A))
        sprite_move(&sprite1, -100, 0);

    if(gl_get_key(context, SDL_SCANCODE_D))
        sprite_move(&sprite1, 100, 0);

    // map_draw(&map0);

    sprite_draw_color(&sprite0, col);

    sprite_draw_texture(&sprite1, &tex0);
}

int main(int argc, char** argv)
{
    engine_create(&engine, 1024, 768, "OpenGL 2D Engine", 32, 4, 6, draw, setup);
    engine_tick(&engine);

    return 0;
}