#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLError.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
int main()
{
	// window stuff
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(960, 540, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
{
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW" << "\n";
	}

	std::cout << glGetString(GL_VERSION) << "\n";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Renderer renderer;
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;
	
	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("Test Texture 2D");
	
	while (!glfwWindowShouldClose(window))
	{
		

		// Start the Dear ImGui frame
		renderer.Clear();	


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		if (currentTest != nullptr)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
			
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		processInput(window);
	}
	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;
}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}