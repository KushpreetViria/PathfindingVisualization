#pragma once
#include "pch.h"

#include <iostream>

#include "Shader.h"
#include "../Logic/Node.h"
#include "../getDir.h"
#include "Square.h"
#include "../Logic/Map.h"

class Graphics
{
public:
	int windowWidth;
	int windowHeight;

	Graphics(int width = 800, int height = 800);
	
	bool initialize();
	void run();

	~Graphics();
private:
	GLFWwindow* window;
	Map* worldMap;
	Shader* myShader;

	GLuint VAO = 0;
	GLuint VBO = 0;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float mouseX = -1;
	float mouseY = -1;




	bool createWindow();	

	void drawGrid();
	void drawNode(float posX, float posY, float tileSizeX, float tileSizeY, Node* curr);
	Node* getNodeUnderMouse();

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_btn_press_callback(GLFWwindow* window, int button, int action, int mods);
	void SetCallbackFunctions();

	class CallbackWrapper{
	public:
		CallbackWrapper() = delete;
		CallbackWrapper(const CallbackWrapper&) = delete;
		CallbackWrapper(CallbackWrapper&&) = delete;
		~CallbackWrapper() = delete;

		static void FramebufferSizeCallback(GLFWwindow* window,int width, int height);
		static void MousePositionCallback(GLFWwindow* window,double positionX, double positionY);
		static void KeyboardPressCallback(GLFWwindow* window,int key, int scancode, int action, int mods);
		static void MouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
		static void SetEngine(Graphics* engine);
	private:
		static Graphics* engine;
	};
};

