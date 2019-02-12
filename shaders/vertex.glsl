#version 410 core

// vbo layout
layout(location=0) in vec3 vertex;
layout(location=1) in vec2 uvs;

// constant
const float screen_x = 800.0;
const float screen_y = 600.0;

// uniforms
uniform vec2 position;
uniform vec2 scale;
uniform float depth = 1;

// other vars
float aspect_ratio;
out vec2 out_uvs;

float linear_convert(float value, float old_min, float old_max, float new_min, float new_max)
{   
    // ((0 - (-1)) * (800 - 0) / (1 - (-1)) + 0) = 400(?)
    return (value - old_min) * (new_max - new_min) / (old_max - old_min) + new_min;
}

void main()
{
    float aspect_ratio = screen_y / screen_x;

    float p_x = linear_convert(position.x, 0, screen_x, -1, 1);
    float p_y = linear_convert(position.y, 0, screen_y, -1, 1);

    float v_x = vertex.x;
    float v_y = vertex.y;

    gl_Position = vec4(vec3(((v_x * scale.x) * aspect_ratio) + p_x, (v_y * scale.y) + (-p_y) , vertex.z), depth);

    out_uvs = uvs;
}