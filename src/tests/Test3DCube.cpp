#include "Test3DCube.h"
#include <gl/glew.h>
#include "../GLError.h"
#include "../vendor/imgui/imgui.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
    TestCube3D::TestCube3D()
        :
        proj(glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f)),
        view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
    {

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
        shader = std::make_unique<Shader>("res/shaders/triangle.glsl");
        shader->Bind();
        shader->SetUniform4f("u_Color", 0.9f, 0.75f, 0.69f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }
    
    TestCube3D::~TestCube3D()
    {
        
    }
    
    void TestCube3D::OnUpdate(float deltaTime)
    {
        
    }
    
    void TestCube3D::OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(.5f, 1.0f, 0.0f));
        glm::scale(model, glm::vec3(0.25f, 0.25f, 1.0f));
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    void TestCube3D::OnImGuiRender()
    {
    }

}