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
    class TestTriangle2D : public Test
    {
    public:
        TestTriangle2D();
        ~TestTriangle2D();
        
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Shader> shader;
        
        glm::mat4 proj, view;
        glm::vec3 translation;
        float color[4];
    };
 };