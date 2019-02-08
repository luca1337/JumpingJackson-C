#version 410 core

out vec4 color;
in vec2 out_uv;

uniform sampler2D tex;

uniform float draw_mode;
uniform vec3 frag_color;

uniform float sprites_per_row;
uniform float sprites_per_column;

uniform float sprite_index;

void main()
{
    if(draw_mode == 0)
    {
        vec2 tex_coords = vec2(out_uv.x, 1-out_uv.y);

        color = texture(tex,  tex_coords);
    }

    if(draw_mode == 1)
    {
        color = vec4(frag_color, 1);
    }
}

// animation
// int sprite_per_row = sprites_per_row;
// int sprite_per_columns = sprites_per_column;

// int sprite_index = sprite_index;

// int x_offset = (sprite_index % sprite_per_row);
// int y_offset = (sprite_index / sprite_per_row);

// vec2 tex_coords = vec2(out_uv.x, 1-out_uv.y);

// color = texture(tex,  vec2(tex_coords.x + x_offset, tex_coords.y + y_offset) / vec2(sprite_per_row, sprite_per_columns));