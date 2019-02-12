#version 410 core

out vec4 color;
in vec2 out_uv;

uniform sampler2D tex;

void main()
{
    // if(out_uv.y > 0.9)
    // {
    //     color = vec4(0, 0, 0, 1);
    // }
    // else if(out_uv.y < 0.1)
    // {
    //     color = vec4(0, 0, 0, 1);
    // }
    // else
    // {
    //     color = texture(tex, vec2(out_uv.x, 1-out_uv.y), 1);
    // }

    vec4 new_color = texture(tex, vec2(out_uv.x, 1-out_uv.y), 1);

    float media = (new_color.x + new_color.y + new_color.z) / 3;

    color = vec4(media, media, media, 1);
}