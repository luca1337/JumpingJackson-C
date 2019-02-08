#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec2 uvs;

const float screen_x = 1024.0;
const float screen_y = 768.0;

uniform vec2 scale;

uniform vec2 position;
uniform float depth = 1;

float aspect_ratio;

out vec2 out_uv;
out vec2 pos_offset;
float ortho_size = 10;

vec3 ortho_proj(vec3 value, float width, float height)
{
    vec3 result;
    result.x = (value.x + 1) * width / 2;
    result.y = (-value.y + 1) * height / 2;
    result.z = vertex.z;
    return result; 
}

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

    //  * aspect_ratio - 0.25 + 0.07

    gl_Position = vec4(vec3(((v_x * scale.x) + p_x), (v_y * scale.y) + (-p_y) , vertex.z), 1);

    pos_offset = position;
    out_uv = uvs;
}