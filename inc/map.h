#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sprite.h>
#include <texture.h>

typedef struct map{
    int width;
    int height;
    int* cells;
    sprite_t* sprites;
    texture_t* tex;
}map_t;

void map_create(map_t* map, int width, int height, float cell_width, float cell_height, int* cells, const char** textures);
void map_draw(map_t* map);