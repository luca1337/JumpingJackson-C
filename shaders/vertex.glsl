#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec2 uvs;

uniform float width;
uniform float height;

uniform vec2 position;
uniform float depth = 1;

out vec2 out_uv;

void main()
{
    gl_Position = vec4(vec3(((vertex.x * width) + position.x)*(600.0/800.0), (vertex.y * height) + position.y, vertex.z), depth);

    out_uv = uvs;
}