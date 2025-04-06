cmake_minimum_required(VERSION 4.0)
project(tetrablocks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

add_executable(tetrablocks
        src/graphics/gl/gl.c
        src/graphics/gl/gl.h
        src/graphics/gl/khrplatform.h
        src/graphics/Shader.cpp
        src/graphics/Shader.hpp
        src/main.cpp
        src/game/TetraGame.cpp
        src/game/TetraGame.hpp
        src/utils/Assets.cpp
        src/utils/Assets.hpp
)

target_include_directories(tetrablocks PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL glm)
target_link_libraries(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL glm)

target_compile_definitions(tetrablocks PRIVATE TETRABLOCKS_ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")