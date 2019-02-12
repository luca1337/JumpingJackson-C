#version 410 core

out vec4 color;

uniform vec3 frag_color;

void main()
{
    color = vec4(frag_color, 1);
}