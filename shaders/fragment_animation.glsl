#version 410 core

// uniforms
uniform int sprites_per_column;
uniform int sprites_per_row;
uniform int x_offset;
uniform int y_offset;
uniform sampler2D tex;

//vertex var
in vec2 out_uvs;

//out var
out vec4 color;

void main()
{
    vec2 tex_coords = vec2(out_uvs.x, 1 - out_uvs.y);

    color = texture(tex,  vec2(tex_coords.x + x_offset, tex_coords.y + y_offset) / vec2(sprites_per_column, sprites_per_row));
}