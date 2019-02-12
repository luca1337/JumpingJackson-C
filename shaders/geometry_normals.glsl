#version 410 core

#version 410 core

layout (triangles) in;
layout (triangle_lines, max_vertices = 6) out;

vec3 get_normal()
{
    vec4 p0 = gl_in[1].gl_Position - gl_in[0].gl_Position;
    vec4 p1 = gl_in[2].gl_Position - gl_in[0].gl_Position;

    return normalize(cross(p0.xyz, p1.xyz));
}

void main()
{
    // code here
}