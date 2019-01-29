#include <shader_utils.h>

static GLuint _compile_shader(GLenum shader_type, const char* shader)
{
    SDL_RWops* rw = SDL_RWFromFile(shader, "rb");
    if(!rw)
    {
        SDL_Log("unable to open file");
        exit(-1);
    }

    size_t file_len = SDL_RWsize(rw);
    char* source = SDL_malloc(file_len + 1);
    if(!source)
    {
        SDL_Log("unable to allocate memory");
        exit(-1);
    }

    if (SDL_RWread(rw, source, 1, file_len) != file_len)
    {
        SDL_Log("unable to read file");
        exit(-1);
    }

    source[file_len] = 0;

    SDL_RWclose(rw);

    GLint shader_final = glCreateShader(shader_type);
    glShaderSource(shader_final, 1, (const GLchar**)&source, (GLint*)&file_len);
    glCompileShader(shader_final);

    SDL_free(source);

    GLint compile_status;
    glGetShaderiv(shader_final, GL_COMPILE_STATUS, &compile_status);
    if(compile_status == GL_FALSE)
    {
        GLint log_size;
        glGetShaderiv(shader_final, GL_INFO_LOG_LENGTH, &log_size);
        char* error_log = malloc(log_size + 1);
        if(!error_log)
        {
            SDL_Log("unable to allocate memory for error_log");
            exit(-1);
        }
        glGetShaderInfoLog(shader_final, log_size, &log_size, error_log);
        SDL_Log("shader compile error: [%s]", error_log);
        exit(-1);
    }

    return shader_final;
}

GLuint compile_shader(const char* vertex, const char* fragment)
{
    GLuint program = glCreateProgram();

    GLuint vertex_shader = _compile_shader(GL_VERTEX_SHADER, vertex);
    GLuint fragment_shader = _compile_shader(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(program);

    return program;
}