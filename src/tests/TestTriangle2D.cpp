#include "TestTriangle2D.h"
#include <gl/glew.h>
#include "../GLError.h"
#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

namespace test
{
    TestTriangle2D::TestTriangle2D()
       : translation(200, 200, 0),
       proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
       view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
       color {1.0f, 1.0f, 1.0f, 1.0f },
       rotation {1.0f, 1.0f, 1.0f},
       scale {1.0f, 1.0f, 1.0f}
    {
        float positions[] = 
        {
            -200.0f, -200.0f, 0.0f, 0.0f,
             200.0f, -200.0f, 1.0f, 0.0f,
             200.0f,  200.0f, 1.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0, 1, 2,
        };
        
        vao = std::make_unique<VertexArray>();
        VertexArray va;
        vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 3 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        vao->AddBuffer(*vertexBuffer, layout);
        indexBuffer = std::make_unique<IndexBuffer>(indices, 3);



        shader = std::make_unique<Shader>("res/shaders/triangle.glsl");
    }
    
    TestTriangle2D::~TestTriangle2D()
    {
        
    }
    
    void TestTriangle2D::OnUpdate(float deltaTime)
    {
        
    }
    void TestTriangle2D::OnRender()
    {
        Renderer renderer; 
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        model = glm::rotate(model, glm::degrees(rotation.x), glm::vec3(1.0, 0.0, 1.0));
        model = glm::rotate(model, glm::degrees(rotation.y), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::degrees(rotation.z), glm::vec3(0.0, 0.0, 1.0));
        
        model = glm::scale(model, scale);
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
        renderer.Draw(*vao, *indexBuffer, *shader);
    }
    
    void TestTriangle2D::OnImGuiRender()
    {
        ImGui::SliderFloat2("Translation A", &translation.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f);
        ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 5.0f);
        ImGui::ColorPicker4("Colors", color);
    }

}