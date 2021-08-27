#pragma once

#include "pch.h"
#include <string>

#define START_KEY GLFW_KEY_S
#define RESET_KEY GLFW_KEY_R
#define DOWN GLFW_KEY_DOWN
#define UP GLFW_KEY_UP

class KeyHandler{
public:
    bool quit;
    bool start;
    bool reset;
    bool key_down;
    bool key_up;
    //state vars here
    KeyHandler();
    void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};