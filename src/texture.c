#include <texture.h>
#include <SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int texture_create(texture_t* texture, const char* file_name)
{
    memset(texture, 0, sizeof(texture_t));

    int width, height, channels;
    unsigned char* pixels = stbi_load(file_name, &width, &height, &channels, 0);
    if(!pixels){
        SDL_Log("could not load image %s", file_name);
        return -1;
    }

    glGenTextures(1, &texture->id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    if(channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // stbi_image_free(pixels);

    return 0;
}