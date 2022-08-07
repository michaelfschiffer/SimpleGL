cmake_minimum_required(VERSION 3.0)
project(SimpleGL)

set(CMAKE_CXX_STANDARD 20)
set(IMGUI_PATH "src/vendor/imgui")

add_executable(SimpleGL 
"src/main.cpp"
"src/IndexBuffer.cpp"
"src/IndexBuffer.h"
"src/Renderer.cpp"
"src/Renderer.h"
"src/VertexArray.cpp"
"src/VertexArray.h"
"src/VertexBuffer.cpp"
"src/VertexBuffer.h"
"src/VertexBufferLayout.h"
"src/Shader.cpp"
"src/Shader.h"
"src/GLError.cpp"
"src/GLError.h"
"src/Texture.cpp"
"src/Texture.h"
"src/vendor/stb_image.cpp"
"src/tests/Test.h"
"src/tests/Test.cpp"
"src/tests/TestClearColor.h"
"src/tests/TestClearColor.cpp"
"src/tests/TestTexture2D.h"
"src/tests/TestTexture2D.cpp"
"src/tests/TestTriangle2D.h"
"src/tests/TestTriangle2D.cpp"
) 

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(SimpleGL PUBLIC glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(SimpleGL PUBLIC glm::glm)

find_package(GLEW REQUIRED)
target_link_libraries(SimpleGL PUBLIC GLEW::GLEW)


find_package(OpenGL REQUIRED)
target_link_libraries(SimpleGL PUBLIC ${OPENGL_gl_LIBRARY})

find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(SimpleGL PUBLIC ${STB_INCLUDE_DIRS})

find_package(glm CONFIG REQUIRED)
target_link_libraries(SimpleGL PUBLIC glm::glm)

file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_link_libraries(SimpleGL PUBLIC ImGui)
target_link_libraries(ImGui PUBLIC glfw)

target_compile_options(SimpleGL PUBLIC /std:c++20 /MP)
add_custom_command(
	TARGET SimpleGL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:SimpleGL>/res
	COMMENT "Copying Resources" VERBATIM
)