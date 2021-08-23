#include "pch.h"
#include "keyHandler.h"

KeyHandler::KeyHandler()
{
}

void KeyHandler::key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    }
}
