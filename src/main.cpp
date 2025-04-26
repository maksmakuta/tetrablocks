#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

#include "tetrablocks/game/Game.hpp"

tetrablocks::Game* getGame(GLFWwindow* window) {
    return static_cast<tetrablocks::Game*>(glfwGetWindowUserPointer(window));
}

void onResize(GLFWwindow* window, const int width, const int height) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onResize(width,height);
    }
}

void onKey(GLFWwindow* window, const int key, int, const int action, const int mods) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onKey(key,action,mods);
    }
}

void onCursor(GLFWwindow * window, const double x, const double y) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onCursor(static_cast<float>(x),static_cast<float>(y));
    }
}

void onButton(GLFWwindow * window, const int button, const int action, const int mods) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onKey(button,action,mods);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,GLFW_TRUE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "TetraBlocks", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    auto game = tetrablocks::Game();
    game.onResize(800,600);
    glfwSetWindowUserPointer(window,&game);

    glfwSetFramebufferSizeCallback(window, onResize);
    glfwSetCursorPosCallback(window, onCursor);
    glfwSetKeyCallback(window,onKey);
    glfwSetMouseButtonCallback(window,onButton);

    auto lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        const auto now = glfwGetTime();
        game.onTick(static_cast<float>(now - lastTime));
        lastTime = now;
        glfwPollEvents();


        game.onDraw();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
