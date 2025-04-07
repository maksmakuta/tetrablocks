cmake_minimum_required(VERSION 4.0)
project(tetrablocks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)
find_package(PNG REQUIRED)

add_executable(tetrablocks
        src/game/TetraGame.cpp
        src/game/TetraGame.hpp

        src/graphics/gl/gl.c
        src/graphics/gl/gl.h
        src/graphics/gl/khrplatform.h
        src/graphics/Font.cpp
        src/graphics/Font.hpp
        src/graphics/Shader.cpp
        src/graphics/Shader.hpp
        src/graphics/Texture.cpp
        src/graphics/Texture.hpp

        src/render/TextRenderer.cpp
        src/render/TextRenderer.hpp

        src/utils/Assets.cpp
        src/utils/Assets.hpp

        src/main.cpp
        src/game/models/Board.cpp
        src/game/models/Board.hpp
        src/game/models/Shape.cpp
        src/game/models/Shape.hpp
        src/render/ShapeRenderer.cpp
        src/render/ShapeRenderer.hpp
)

target_include_directories(tetrablocks PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL PNG::PNG glm)
target_link_libraries(tetrablocks PRIVATE glfw Freetype::Freetype OpenGL::OpenGL PNG::PNG glm)

target_compile_definitions(tetrablocks PRIVATE TETRABLOCKS_ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")