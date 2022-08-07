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
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();
        
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;
        
        glm::mat4 proj, view;
        glm::vec3 translationA, translationB;
    };
 };