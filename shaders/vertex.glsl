#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec2 uvs;

uniform float width = 0.2;
uniform float height = 0.2;

uniform vec2 position;
uniform float depth = 1;

out vec2 out_uv;

float linear_convert(float value, float old_min, float old_max, float new_min, float new_max)
{
    float gradient = (value - old_min) / (old_max - old_min);
    return new_min + gradient * (new_max - new_min);
}

void main()
{
    gl_Position = vec4(vec3(((vertex.x * width) + position.x)*(600.0/800.0) - 0.2, (vertex.y * height) + position.y, vertex.z), depth);

    out_uv = uvs;
}