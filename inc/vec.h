#ifndef VEC_H
#define VEC_H

typedef struct vec2{
    float x;
    float y;
}vec2_t;

typedef struct vec3{
    float x;
    float y;
    float z;
}vec3_t;

vec2_t vec2_init(float, float);
vec2_t vec2_sum(vec2_t, vec2_t);
vec2_t vec2_sub(vec2_t, vec2_t);
vec2_t vec2_scale(vec2_t, vec2_t);
float vec2_slow_len(vec2_t);
float vec2_fast_len(vec2_t);
float vec2_dist(vec2_t, vec2_t);
int vec2_normalize(vec2_t*);
vec2_t vec2_scaled(vec2_t, float);
float vec2_dot(vec2_t, vec2_t);
vec2_t vec2_reflected(vec2_t, vec2_t);

// vec3
vec3_t vec3_init(float, float, float);
vec3_t vec3_sum(vec3_t, vec3_t);
vec3_t vec3_sub(vec3_t, vec3_t);
vec3_t vec3_scale(vec3_t, vec3_t);
float vec3_slow_len(vec3_t);
float vec3_fast_len(vec3_t);
float vec3_dist(vec3_t, vec3_t);
int vec3_normalize(vec3_t*);
vec3_t vec3_scaled(vec3_t, float);
float vec3_dot(vec3_t, vec3_t);
vec3_t vec3_reflected(vec3_t, vec3_t);

#endif