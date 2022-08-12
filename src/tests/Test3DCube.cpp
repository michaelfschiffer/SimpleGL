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

        // using an index buffer, a cube can be crated from just the front and back faces
        float positions [] =
        {
            // front face
            -0.5f,  0.5f,  0.5f, // top-left 0
            -0.5f, -0.5f,  0.5f, // bottom-left 1
             0.5f,  0.5f,  0.5f, // top-right 2
             0.5f, -0.5f,  0.5f, // bottom-right 3
            // back face
            -0.5f,  0.5f, -0.5f, // top-left 4
            -0.5f, -0.5f, -0.5f, // bottom-left 5
             0.5f,  0.5f, -0.5f, // top-right 6
             0.5f, -0.5f, -0.5f  // bottom-right 7
        };
        // 6 faces * 2 triangles = 12 triangles
        // vertices were defined CCW above, so top-right->bottom-left->top-left
        unsigned int indices [] =
        {
        // front face
            0,1,2,
            1,3,2,
        
        // Back Face
           4,5,6,
           5,7,6,
        
        // Top Face
           6,0,4,
           2,6,0,
        // Bottom Face
           1,5,7,
           1,3,7,
        // Right Face
           2,3,6,
           3,7,6,
        // Left Face
           1,5,4,
           4,5,1
        };
        vao = std::make_unique<VertexArray>();
        vertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        vao->AddBuffer(*vertexBuffer, layout);
        indexBuffer = std::make_unique<IndexBuffer>(indices, 36);

            
        shader = std::make_unique<Shader>("res/shaders/triangle.glsl");
        shader->Bind();
        shader->SetUniform4f("u_Color", 0.9f, 0.75f, 0.69f, 1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    TestCube3D::~TestCube3D()
    {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }
    
    void TestCube3D::OnUpdate(float deltaTime)
    {
        
    }
    
    void TestCube3D::OnRender()
    {
        Renderer renderer;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*vao, *indexBuffer, *shader);
    }
    
    void TestCube3D::OnImGuiRender()
    {
      ImGui::Checkbox("Enable Rotation", &rotating);
    }

}
