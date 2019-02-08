#include <sprite.h>
#include <engine.h>

extern engine_t engine;

static void sprite_mesh_cache_uniform(sprite_t* sprite)
{
    sprite->shader_prg.scale = glGetUniformLocation(engine.program, "scale");
    sprite->shader_prg.position = glGetUniformLocation(engine.program, "position");
    sprite->shader_prg.draw_mode = glGetUniformLocation(engine.program, "draw_mode");
    sprite->shader_prg.color = glGetUniformLocation(engine.program, "frag_color");
    sprite->shader_prg.tex = glGetUniformLocation(engine.program, "tex");

    sprite->shader_prg.sprites_per_row = glGetUniformLocation(engine.program, "sprites_per_row");
    sprite->shader_prg.sprites_per_col = glGetUniformLocation(engine.program, "sprites_per_column");
    sprite->shader_prg.sprite_index = glGetUniformLocation(engine.program, "sprite_index");
}

int sprite_create(sprite_t* sprite, float width, float height)
{
    glGenVertexArrays(1, &sprite->vao);
    glBindVertexArray(sprite->vao);

     //quad(?) vertices
    GLfloat vertices[] = {
        -0.5, 0.5, 0.0,//a
        0.5, -0.5, 0.0,//b
        0.5, 0.5, 0.0,//c

        -0.5, 0.5, 0.0,//a
        -0.5, -0.5, 0.0,//b
        0.5, -0.5, 0.0//c
    };

    //uvs
    GLfloat uvs[] = {
        0,1,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0
    };

    GLuint vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    sprite_mesh_cache_uniform(sprite);

    sprite->width = width * (engine.context.width / 2);
    sprite->height = height * (engine.context.height / 2);

    sprite_set_scale(sprite, width, height);

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
    sprite->scale.x = x;
    sprite->scale.y = y;
}

void sprite_set_color(sprite_t* sprite, const vec3_t color)
{
    sprite->color = color;
}

void sprite_draw_color(sprite_t* sprite, vec3_t color)
{
    glUseProgram(engine.program);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    sprite_set_color(sprite, color);
    glUniform1f(sprite->shader_prg.draw_mode, 1);
    glUniform2f(sprite->shader_prg.scale, sprite->scale.x, sprite->scale.y);
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    glUniform3f(sprite->shader_prg.color, sprite->color.x, sprite->color.y, sprite->color.z);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void sprite_draw_texture(sprite_t* sprite, texture_t* texture)
{
    glUseProgram(engine.program);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    glUniform1f(sprite->shader_prg.draw_mode, 0);
    glUniform2f(sprite->shader_prg.scale, sprite->scale.x, sprite->scale.y);
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}