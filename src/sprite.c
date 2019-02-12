#include <sprite.h>
#include <engine.h>

extern engine_t engine;

static void sprite_mesh_cache_uniform(sprite_t* sprite)
{
    // questo è provvisorio

    sprite->shader_prg.position = glGetUniformLocation(engine.base_color, "position");
    sprite->shader_prg.scale = glGetUniformLocation(engine.base_color, "scale");
    sprite->shader_prg.color = glGetUniformLocation(engine.base_color, "frag_color");

    sprite->shader_prg.sprites_per_col = glGetUniformLocation(engine.base_color, "sprites_per_column");
    sprite->shader_prg.sprites_per_row = glGetUniformLocation(engine.base_color, "sprites_per_row");
    sprite->shader_prg.x_offset = glGetUniformLocation(engine.base_color, "x_offset");
    sprite->shader_prg.y_offset = glGetUniformLocation(engine.base_color, "y_offset");
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

void sprite_draw_color(sprite_t* sprite, vec3_t color, GLuint program)
{
    if(!program)
        glUseProgram(engine.base_color);
    else
        glUseProgram(program);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    sprite_set_color(sprite, color);
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    glUniform2f(sprite->shader_prg.scale, sprite->scale.x, sprite->scale.y);
    glUniform3f(sprite->shader_prg.color, sprite->color.x, sprite->color.y, sprite->color.z);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void sprite_draw_texture(sprite_t* sprite, texture_t* texture, GLuint program)
{
    if(!program)
        glUseProgram(engine.texture);
    else
        glUseProgram(program);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glBindVertexArray(sprite->vao);

    //bind uniforms
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    glUniform2f(sprite->shader_prg.scale, sprite->scale.x, sprite->scale.y);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void sprite_draw_texture_offset(sprite_t* sprite, texture_t* texture, int x_offset, int y_offset, int sprites_in_row, int sprites_in_column, GLuint program)
{
    if(!program)
        glUseProgram(engine.animation);
    else
        glUseProgram(program);

    glBindTexture(GL_TEXTURE0, texture->id);

    glBindVertexArray(sprite->vao);

    // Bind uniforms
    glUniform2f(sprite->shader_prg.position, sprite->position.x, sprite->position.y);
    glUniform2f(sprite->shader_prg.scale, sprite->scale.x, sprite->scale.y);
    glUniform1i(sprite->shader_prg.sprites_per_row, sprites_in_row);
    glUniform1i(sprite->shader_prg.sprites_per_col, sprites_in_column);
    glUniform1i(sprite->shader_prg.x_offset, x_offset);
    glUniform1i(sprite->shader_prg.y_offset, y_offset);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}