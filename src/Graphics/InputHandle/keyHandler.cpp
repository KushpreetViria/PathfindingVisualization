#include "pch.h"
#include "keyHandler.h"

KeyHandler::KeyHandler()
{
    quit = false;
    start = false;
    reset = false;
}

void KeyHandler::key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            quit = true;
        else if (key == START_KEY) {
            start = true;
        }else if (key == RESET_KEY) {
            reset = true;
        }
    }
}
