CMAKE_MINIMUM_REQUIRED(VERSION 3.30 FATAL_ERROR)
project(tetrablocks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/LodePNG)

add_executable(tetrablocks

        include/tetrablocks/game/core/Assets.hpp
        include/tetrablocks/game/core/IDialog.hpp
        include/tetrablocks/game/core/IController.hpp
        include/tetrablocks/game/core/IScreen.hpp
        include/tetrablocks/game/screen/ScreenGame.hpp
        include/tetrablocks/game/screen/ScreenMain.hpp
        include/tetrablocks/game/ui/Button.hpp
        include/tetrablocks/game/Game.hpp
        include/tetrablocks/graphics/Font.hpp
        include/tetrablocks/graphics/Renderer.hpp
        include/tetrablocks/graphics/Shader.hpp
        include/tetrablocks/graphics/Texture.hpp
        include/tetrablocks/model/Board.hpp
        include/tetrablocks/model/Block.hpp
        include/tetrablocks/model/Shape.hpp
        include/tetrablocks/Constants.hpp
        include/tetrablocks/Utils.hpp

        src/game/screen/ScreenGame.cpp
        src/game/screen/ScreenMain.cpp
        src/game/ui/Button.cpp
        src/game/Game.cpp
        src/graphics/Font.cpp
        src/graphics/Renderer.cpp
        src/graphics/Shader.cpp
        src/graphics/Texture.cpp
        src/model/Block.cpp
        src/model/Board.cpp
        src/model/Shape.cpp
        src/Utils.cpp
        src/main.cpp

)

target_link_libraries(tetrablocks PUBLIC glfw OpenGL::GL GLAD LodePNG glm::glm Freetype::Freetype)
target_include_directories(tetrablocks PUBLIC include)
target_compile_definitions(tetrablocks PUBLIC ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")