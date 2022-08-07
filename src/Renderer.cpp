#include "Renderer.h"
#include <iostream>
#include "GLError.h"


void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind(); 
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
