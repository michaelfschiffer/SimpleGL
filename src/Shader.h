#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "GLError.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

enum class ShaderType
{
    None = -1, Vertex = 0, Fragment = 1
};

class Shader
{
private:
    unsigned int rendererID;
    std::string filePath;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float f0, float f1,float f2, float f3);
    void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);
    inline unsigned int GetRendererID() { return rendererID; };
private:
    ShaderProgramSource ParseShader(const std::string& filePath);
    int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(const unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);

    






};