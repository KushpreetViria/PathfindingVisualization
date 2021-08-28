#include "pch.h"
#include "keyHandler.h"
#include <iostream>

KeyHandler::KeyHandler()
{
    quit = false;
    start = false;
    reset = false;
    key_down = false;
    key_up = false;
}

void KeyHandler::key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE){
            quit = true;
        } else if (key == START_KEY) {
            start = true;
        } else if (key == RESET_KEY) {
            reset = true;
        } else if (key == DOWN) {
            key_down = true;
        } else if (key == UP) {
            key_up = true;
        }else if (key == ALGO_CHANGE) {
            algo_change = true;
        }
    }else if (action == GLFW_RELEASE) {
        if (key == START_KEY) {
            start = false;
        } else if (key == RESET_KEY) {
            reset = false;
        } else if (key == DOWN) {
            key_down = false;
        } else if (key == UP) {
            key_up = false;
        }else if (key == ALGO_CHANGE) {
            algo_change = false;
        }
    }
}
