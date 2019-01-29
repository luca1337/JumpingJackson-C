#version 410 core

out vec4 color;
in vec2 out_uv;

uniform vec3 sprite_color;

uniform sampler2D tex;

void main()
{
    color = texture(tex, out_uv);
}