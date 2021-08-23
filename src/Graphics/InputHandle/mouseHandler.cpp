#include "pch.h"
#include "MouseHandler.h"

MouseHandler::MouseHandler()
{
	mouseX = -1;
	mouseY = -1;
	doubleClickHold= false;
	singleClickkHold = false;
	firstClick = true;
}

void MouseHandler::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	this->mouseX = (float)xpos;
	this->mouseY = (float)ypos;
}

void MouseHandler::mouse_btn_press_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (firstClick) {
		lastClick = high_res_clock::now();
		singleClickkHold = true;
		firstClick = false;
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		auto currTime = high_res_clock::now();
		duration ms_double = currTime - lastClick;
		std::cout << ms_double.count() << std::endl;
		if (ms_double.count() < DOUBLE_CLICK_SPEED_MS) {
			doubleClickHold = true;
		}
		singleClickkHold = true;
		lastClick = currTime;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		doubleClickHold = false;
		singleClickkHold = false;
	}
}
