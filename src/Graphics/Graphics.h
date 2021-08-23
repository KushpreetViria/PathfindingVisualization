#pragma once
#include "pch.h"

#include <iostream>

#include "Shader.h"
#include "../getDir.h"
#include "Square.h"
#include "InputHandle/mouseHandler.h"
#include "InputHandle/keyHandler.h"

#include "../Logic/Node.h"
#include "../Logic/Map.h"

class Graphics
{
public:
	int windowWidth;
	int windowHeight;

	Graphics(Map* map,int width = 800, int height = 800);
	
	bool initialize();
	void run();

	~Graphics();
private:
	GLFWwindow* window;
	Map* worldMap;
	Shader* myShader;

	MouseHandler mouseHandle;
	KeyHandler keyHandle;

	GLuint VAO = 0;
	GLuint VBO = 0;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;




	bool createWindow();	

	void drawGrid();
	void drawNode(float posX, float posY, float tileSizeX, float tileSizeY, Node* curr);
	Node* getNodeUnderMouse();

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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
		
		static void SetGraphics(Graphics* graphics);
		static void SetMouseHandler(MouseHandler* mh);
		static void SetKeyHandler(KeyHandler* kh);
	private:
		static Graphics* graphics;
		static MouseHandler* mouseHandle;
		static KeyHandler* keyHandle;
	};
};

