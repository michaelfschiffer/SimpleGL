#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GLCall(glGenBuffers(1, &rendererID));
	// * How the buffer is going to be used (Vertex Attributes)
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}