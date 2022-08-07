#include "TestTexture2D.h"
#include <gl/glew.h>
#include "../GLError.h"
#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

namespace test
{
    TestTexture2D::TestTexture2D()
       : translationA(200, 200, 0),
       translationB(400, 200, 0),
       proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
       view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
       
    {
        float positions[] = 
        {
            -50.0f, -50.0f, 0.0f, 0.0f,
             50.0f, -50.0f, 1.0f, 0.0f,
             50.0f,  50.0f, 1.0f, 1.0f,
            -50.0f,  50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        vao = std::make_unique<VertexArray>();
        VertexArray va;
        vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vao->AddBuffer(*vertexBuffer, layout);
        indexBuffer = std::make_unique<IndexBuffer>(indices, 6);


        shader = std::make_unique<Shader>("res/shaders/Basic.glsl");
        shader->Bind();
        texture = std::make_unique<Texture>("res/textures/gl.png");
        shader->SetUniform1i("u_Texture", 0);

    }
    
    TestTexture2D::~TestTexture2D()
    {
        
    }
    
    void TestTexture2D::OnUpdate(float deltaTime)
    {
        
    }
    
    void TestTexture2D::OnRender()
    {
        Renderer renderer;
        texture->Bind();
        {        
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model;
            shader->Bind();
            shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*vao, *indexBuffer, *shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;
            shader->Bind();
            shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*vao, *indexBuffer, *shader);
        }
     
    }
    
    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat2("Translation A", &translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat2("Translation B", &translationB.x, 0.0f, 960.0f);
    }

}