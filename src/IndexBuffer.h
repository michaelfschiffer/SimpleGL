#pragma once
#include "GLError.h"
#include <gl/glew.h>

class IndexBuffer
{
    private:
        unsigned int rendererID;
        unsigned int count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return count; }
};