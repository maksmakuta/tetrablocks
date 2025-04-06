cmake_minimum_required(VERSION 4.0)
project(tetrablocks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

add_executable(tetrablocks src/main.cpp)

target_include_directories(tetrablocks PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL glm)
target_link_libraries(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL glm)