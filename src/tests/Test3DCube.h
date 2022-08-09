#pragma once
#include "Test.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../Renderer.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include <glm/glm.hpp>
#include <memory>

namespace test
{
    class TestCube3D : public Test
    {
    public:
        TestCube3D();
        ~TestCube3D();
        
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        
    private:
        std::unique_ptr<Shader> shader;
        unsigned int vao,vbo;
        glm::mat4 proj, view;
        glm::vec3 translationA;
        float positions[108] =
        {
             -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, 0.5f, -0.5f,
             0.5f, 0.5f, -0.5f,
             -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f, 
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f, 
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f, 
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f, 

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f, 
            0.5f, 0.5f, 0.5f,   

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f, 
            0.5f, -0.5f, 0.5f, 
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f, 
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f, 
            -0.5f, 0.5f, -0.5f

        };
    };
 };