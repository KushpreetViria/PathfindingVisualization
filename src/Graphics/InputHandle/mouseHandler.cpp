#include "pch.h"
#include "MouseHandler.h"

MouseHandler::MouseHandler()
{
	mouseX = -1;
	mouseY = -1;
	singleClickkHoldLeft = false;
	doubleClickHoldLeft = false;
	singleClickkHoldRight = false;
	doubleClickHoldRight = false;

	firstClickLeft = true;
	firstClickRight = true;
}

void MouseHandler::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	this->mouseX = (float)xpos;
	this->mouseY = (float)ypos;
}

void MouseHandler::mouse_btn_press_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		if (firstClickLeft && button == GLFW_MOUSE_BUTTON_LEFT) {
			lastClickLeft = high_res_clock::now();
			singleClickkHoldLeft = true;
			firstClickLeft = false;			
			return;
		}
		else if (firstClickRight && button == GLFW_MOUSE_BUTTON_RIGHT) {
			lastClickRight = high_res_clock::now();
			singleClickkHoldRight = true;
			firstClickRight = false;
			return;
		}

		auto currTime = high_res_clock::now();
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			duration ms_double = currTime - lastClickLeft;
			if (ms_double.count() < DOUBLE_CLICK_SPEED_MS) {
				doubleClickHoldLeft = true;
			}
			singleClickkHoldLeft = true;
			lastClickLeft = currTime;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			duration ms_double = currTime - lastClickRight;
			if (ms_double.count() < DOUBLE_CLICK_SPEED_MS) {
				doubleClickHoldRight = true;
			}
			singleClickkHoldRight = true;
			lastClickRight = currTime;
		}
	}
	else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			doubleClickHoldLeft = false;
			singleClickkHoldLeft = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			doubleClickHoldRight = false;
			singleClickkHoldRight = false;
		}
	}
}