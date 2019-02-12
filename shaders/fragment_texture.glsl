#version 410 core

in vec2 out_uvs;

uniform sampler2D tex;

out vec4 color;

void main()
{
    vec2 texture_offsets = vec2(out_uvs.x, 1 - out_uvs.y);
    
    color = texture(tex, texture_offsets);
}