#pragma once
#include <pch.h>

#include <iostream>
#include <string>
#include <chrono>

constexpr auto DOUBLE_CLICK_SPEED_MS = 500;

class MouseHandler {
public:
	float mouseX;
	float mouseY;
	bool firstClick; 
	bool singleClickkHold;
	bool doubleClickHold;

	MouseHandler();

	void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_btn_press_callback(GLFWwindow* window, int button, int action, int mods);
private:
	using my_time_point = std::chrono::steady_clock::time_point;
	using high_res_clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<double,std::milli>;
	my_time_point lastClick;
};