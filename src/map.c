#include <map.h>
#include <SDL.h>

void map_create(map_t* map, int width, int height, int* cells, const char** textures)
{
    map->cells = malloc(sizeof(int) * (width * height));

    map->width = width;
    map->height = height;

    memcpy(map->cells, cells, sizeof(int) * (map->width * map->height));

    map->sprites = malloc(sizeof(sprite_t) * (map->width * map->height));

    for(int i = 0; i < map->width * map->height; i++)
    {
        // sprite_create(&map->sprites[i], 0.2, 0.2, textures[map->cells[i]]);
    }
}

void map_draw(map_t* map)
{
    for(int i = 0; i < map->width * map->height; i++)
    {
        float offset_x = (i % map->width) * map->sprites[i].width;
        float offset_y = (i / map->height) * map->sprites[i].height;

        sprite_set_position(&map->sprites[i], offset_x, offset_y);
        // sprite_draw_texture(&map->sprites[i]);
    }
}