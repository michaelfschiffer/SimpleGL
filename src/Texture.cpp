#include "Texture.h"
#include "GLError.h"
#include <gl/glew.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& filePath)
    :
    rendererID(0),
    filePath(filePath),
    localBuffer(nullptr),
    width(0),
    height(0),
    bpp(0)
{
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
    GLCall(glGenTextures(1, &rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


    if (localBuffer)
    {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
        GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
        stbi_image_free(localBuffer);
    }
    else
    {
        std::cout << "\nError: Failed to load texture\n" << stbi_failure_reason() << "\n";
        __debugbreak();
    }
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &rendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}