#pragma once

#include "pch.h"
#include <string>

class KeyHandler{
public:
    //state vars here
    KeyHandler();
    void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};