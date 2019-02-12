#define SDL_MAIN_HANDLED

#include <engine.h>
#include <sprite.h>
#include <vec.h>
#include <map.h>

engine_t engine;

sprite_t sprite0;
texture_t tex0;

vec3_t col;

int sprites_per_column = 7;
int sprites_per_row = 4;
int num_of_key_frames = 4;
int key_frames[] = { 0, 1, 2, 3 };
float frame_length = 0.04;
float timer;
int k_index;
int current_index;

static void setup(engine_t* engine)
{
    texture_create(&tex0, "assets/textures/oc.png");

    col = vec3_init(1, 0, 0);

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

    // sprite_draw_texture(&sprite0, &tex0, 0);

    /* timer += context->delta_time;
    if(timer > frame_length)
    {
        if(k_index > num_of_key_frames)
        {
            current_index = key_frames[0];
            k_index = 0;
        }
        current_index = key_frames[k_index++];
        timer = 0.0;
    }

    int x_offset = (current_index % sprites_per_row);
    int y_offset = (current_index / sprites_per_row);

    sprite_draw_texture_offset(&sprite0,
                                &tex0,
                                x_offset,
                                y_offset,
                                sprites_per_row,
                                sprites_per_column,
                                0); */
}

int main(int argc, char** argv)
{
    engine_create(&engine, 800, 600, "OpenGL 2D Engine", 32, 4, 6, draw, setup, NULL);
    engine_tick(&engine);

    return 0;
}