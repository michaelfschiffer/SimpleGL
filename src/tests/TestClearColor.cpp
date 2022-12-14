#include "TestClearColor.h"
#include <gl/glew.h>
#include "../GLError.h"
#include "../vendor/imgui/imgui.h"

namespace test
{
    TestClearColor::TestClearColor()
        : 
        clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
    {
    
    }
    
    TestClearColor::~TestClearColor()
    {
        
    }
    
    void TestClearColor::OnUpdate(float deltaTime)
    {
        
    }
    
    void TestClearColor::OnRender()
    {
       GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3])); 
       GLCall(glClear(GL_COLOR_BUFFER_BIT)); 
    }
    
    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", clearColor); 
    }

}