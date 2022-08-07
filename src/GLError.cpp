#include "GLError.h"
#include <gl/glew.h>
#include <iostream>


void GLClearError()
{
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (0x" << std::hex << error << "): " << function << "\n"
		<< " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}