#pragma once

#include "pch.h"
#include <string>

#define START_KEY GLFW_KEY_S
#define RESET_KEY GLFW_KEY_R

class KeyHandler{
public:
    bool quit;
    bool start;
    bool reset;
    //state vars here
    KeyHandler();
    void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};