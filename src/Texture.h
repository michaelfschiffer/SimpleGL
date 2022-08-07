#pragma once
#include <string>

class Texture
{
private:
    unsigned int rendererID;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, bpp;
public:
    Texture(const std::string& filePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
};