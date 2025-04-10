#include "graphics/gl/gl.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "game/TetraGame.hpp"

tetrablocks::game::TetraGame* getGame(GLFWwindow* win) {
    return static_cast<tetrablocks::game::TetraGame *>(glfwGetWindowUserPointer(win));
}

void onResize(GLFWwindow * window, const int width, const int height) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onResize(width,height);
    }
}

void onCursor(GLFWwindow * window, const double x, const double y) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onCursor(static_cast<float>(x),static_cast<float>(y));
    }
}

void onKey(GLFWwindow * window, const int key, int , const int action, const int mods) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onKey(key,action,mods);
    }
}

void onButton(GLFWwindow * window, const int button, const int action, const int mods) {
    if (const auto game = getGame(window); game != nullptr) {
        game->onKey(button,action,mods);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Cannot init GLFW library" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_VERSION_MINOR,3);
    glfwWindowHint(GLFW_SAMPLES,8);

    GLFWwindow* win = glfwCreateWindow(800,600,"TetraBlocks",nullptr,nullptr);
    if (!win) {
        std::cerr << "Cannot create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(win);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Cannot load OpenGL library" << std::endl;
        glfwDestroyWindow(win);
        glfwTerminate();
        return -1;
    }

    auto game = tetrablocks::game::TetraGame();
    glfwSetWindowUserPointer(win,&game);

    glfwSetWindowSizeCallback(win,onResize);
    glfwSetCursorPosCallback(win,onCursor);
    glfwSetKeyCallback(win,onKey);
    glfwSetMouseButtonCallback(win,onButton);

    double lastTime = glfwGetTime();
    game.init();
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();

        const double now = glfwGetTime();
        game.update(static_cast<float>(now - lastTime));
        lastTime = now;

        game.draw();

        glfwSwapBuffers(win);
    }
    game.deinit();

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
