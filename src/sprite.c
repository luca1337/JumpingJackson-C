#include <sprite.h>
#include <engine.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

extern engine_t engine;

static void sprite_mesh_cache_uniform(sprite_t* sprite)
{
    sprite->shader_prg.width = glGetUniformLocation(engine.program, "width");
    sprite->shader_prg.height = glGetUniformLocation(engine.program, "height");
    sprite->shader_prg.position = glGetUniformLocation(engine.program, "position");
    sprite->shader_prg.color = glGetUniformLocation(engine.program, "sprite_color");
}

static void mesh_add_texture(sprite_t* sprite, int width, int height, int channels, unsigned char* pixels)
{
    glGenTextures(1, &sprite->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->tex);
    if(channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(pixels);
}

int sprite_create(sprite_t* sprite, float width, float height, const char* texture)
{
    memset(sprite, 0, sizeof(sprite_t));

    glGenVertexArrays(1, &sprite->vao);
    glBindVertexArray(sprite->vao);

     //quad(?) vertices
    GLfloat vertices[] = {
        -0.5, 0.5, 0.0,//a
        0.5, 0.5, 0.0,//b
        0.5, -0.5, 0.0,//c

        -0.5, 0.5, 0.0,//a
        -0.5, -0.5, 0.0,//b
        0.5, -0.5, 0.0//c
    };

    //uvs
    GLfloat uvs[] = {
        -1, 1,
        1, 1,
        1, -1,
        -1, 1,
        -1, -1,
        1, -1
    };

    GLuint vbo[2];
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    int w,h,channels;
    unsigned char* pixels = stbi_load(texture, &w, &h, &channels, 0);

    mesh_add_texture(sprite, w, h, channels, pixels);

    sprite_mesh_cache_uniform(sprite);

    sprite->width = w;
    sprite->height = h;

    return 0;
}

void sprite_move(sprite_t* sprite, float x, float y)
{
    sprite->position.x += x * engine.context.delta_time;
    sprite->position.y += y * engine.context.delta_time;
}

void sprite_set_position(sprite_t* sprite, float x, float y)
{
    sprite->position.x = x;
    sprite->position.y = y;
}

void sprite_set_scale(sprite_t* sprite, float x, float y)
{
    sprite->width = x;
    sprite->height = y;
}

void sprite_draw_color(sprite_t* sprite, const vec3_t color)
{
    glUseProgram(engine.program);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    sprite_set_color(sprite, color);
    glUniform1f(sprite->shader_prg.width, sprite->width);
    glUniform1f(sprite->shader_prg.height, sprite->height);
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    glUniform3f(sprite->shader_prg.color, sprite->color.x, sprite->color.y, sprite->color.z);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void sprite_set_color(sprite_t* sprite, const vec3_t color)
{
    sprite->color = color;
}

void sprite_draw_texture(sprite_t* sprite)
{
    glUseProgram(engine.program);

    glBindTexture(GL_TEXTURE_2D, sprite->tex);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    // glUniform1f(sprite->shader_prg.width, sprite->width);
    // glUniform1f(sprite->shader_prg.height, sprite->height);
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    // glUniform3f(sprite->shader_prg.color, sprite->color.x, sprite->color.y, sprite->color.z);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}