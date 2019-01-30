#version 410 core

out vec4 color;
in vec2 out_uv;

uniform sampler2D tex;

uniform float draw_mode;

uniform vec3 frag_color;

void main()
{
    if(draw_mode == 0)
    {
        color = texture(tex, vec2(out_uv.x, 1-out_uv.y));
    }

    if(draw_mode == 1)
    {
        color = vec4(frag_color, 1);
    }
}