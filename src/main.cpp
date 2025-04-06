#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

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

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}