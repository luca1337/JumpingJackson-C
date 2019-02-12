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
int num_of_key_frames = 16;
int key_frames[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 10, 11, 12, 13, 14, 15, 16 };
float frame_length = 0.02;
float timer;
int k_index;
int current_index;

typedef struct node{
    void** data;
    struct node* next;
    struct node* prev;
}node_t;

typedef struct list{
    node_t* head;
    node_t* tail;
    size_t count;
}list_t;

void list_append(list_t* list, void* data)
{
    node_t* item = malloc(sizeof(node_t));
    item->data = malloc(sizeof(data));

    if(!list->head)
    {
        item->data = data;
        list->head = item;
        list->tail = item;
        list->count++;
        return;
    }

    list->tail->next = item;
    item->prev = list->tail;
    list->tail = item;
    item->data = data;
    list->count++;
}

void* list_get(list_t* list, void* data)
{
    void* ret = NULL;

    node_t* item = list->head;

    while(item)
    {
        SDL_Log("iter");
        if(!memcmp(item->data, data, sizeof(data)))
        {
            SDL_Log("found!");
            ret = item->data;
            return ret;
        }

        item = item->next;
    }

    return ret;
}

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

    // sprite_draw_color(&sprite0, col, 0);

    // sprite_draw_texture(&sprite0, &tex0, 0);

    timer += context->delta_time;
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
                                0);
}

int main(int argc, char** argv)
{
    engine_create(&engine, 800, 600, "OpenGL 2D Engine", 32, 4, 6, draw, setup, NULL);
    engine_tick(&engine);

    return 0;
}