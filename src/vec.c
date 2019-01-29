#include <vec.h>
#include <stdio.h>
#include <math.h>

vec2_t vec2_init(float x, float y)
{
    vec2_t result;
    result.x = x;
    result.y = y;
    return result;
}

vec2_t vec2_sum(vec2_t v0, vec2_t v1)
{
    vec2_t result;
    result.x = v0.x + v1.x;
    result.y = v0.y + v1.y;
    return result;
}

vec2_t vec2_sub(vec2_t v0, vec2_t v1)
{
    vec2_t result;
    result.x = v0.x - v1.x;
    result.y = v0.y - v1.y;
    return result;
}

vec2_t vec2_scale(vec2_t v0, vec2_t v1)
{
    vec2_t result;
    result.x = v0.x * v1.x;
    result.y = v0.y * v1.y;
    return result;
}

vec2_t vec2_scaled(vec2_t v, float s)
{
    return vec2_init(v.x * s, v.y * s); 
}

float vec2_dot(vec2_t v1, vec2_t v2)
{
    return v1.x * v2.x + v1.y * v2.y; 
}

vec2_t vec2_reflected(vec2_t v, vec2_t n)
{
    return vec2_sub(v, vec2_scaled(n, 2 * vec2_dot(v, n)));    
}

float vec2_slow_len(vec2_t v)
{
    return (float)sqrt(pow(v.x, 2) + pow(v.y, 2));
}

float vec2_fast_len(vec2_t v)
{
    return (pow(v.x, 2) + pow(v.y, 2));
}

float vec2_dist(vec2_t v0, vec2_t v1)
{
    vec2_t result = vec2_sub(v0, v1);
    return vec2_slow_len(result);
}

int vec2_normalize(vec2_t* v)
{
    float v_len = vec2_slow_len(*v);
    v->x = v->x / v_len;
    v->y = v->y / v_len;
    return 0;
}

//vec3

vec3_t vec3_init(float x, float y, float z)
{
    vec3_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

vec3_t vec3_sum(vec3_t v0, vec3_t v1)
{
    vec3_t result;
    result.x = v0.x + v1.x;
    result.y = v0.y + v1.y;
    result.z = v0.z + v1.z;
    return result;
}

vec3_t vec3_sub(vec3_t v0, vec3_t v1)
{
    vec3_t result;
    result.x = v0.x - v1.x;
    result.y = v0.y - v1.y;
    result.z = v0.z - v1.z;
    return result;
}

vec3_t vec3_scale(vec3_t v0, vec3_t v1)
{
    vec3_t result;
    result.x = v0.x * v1.x;
    result.y = v0.y * v1.y;
    result.z = v0.y * v1.z;
    return result;
}

vec3_t vec3_scaled(vec3_t v, float s)
{
    return vec3_init(v.x * s, v.y * s, v.z * s); 
}

float vec3_dot(vec3_t v1, vec3_t v2)
{
    return v1.x * v2.x + v1.y * v2.y * v1.z * v2.z; 
}

vec3_t vec3_reflected(vec3_t v, vec3_t n)
{
    return vec3_sub(v, vec3_scaled(n, 3 * vec3_dot(v, n)));    
}

float vec3_slow_len(vec3_t v)
{
    return (float)sqrt(pow(v.x, 3) + pow(v.y, 3));
}

float vec3_fast_len(vec3_t v)
{
    return (pow(v.x, 3) + pow(v.y, 3));
}

float vec3_dist(vec3_t v0, vec3_t v1)
{
    vec3_t result = vec3_sub(v0, v1);
    return vec3_slow_len(result);
}

int vec3_normalize(vec3_t* v)
{
    float v_len = vec3_slow_len(*v);
    v->x = v->x / v_len;
    v->y = v->y / v_len;
    v->z = v->z / v_len;
    return 0;
}