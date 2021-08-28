#pragma once
#include "pch.h"

#include <iostream>

#include "Shader.h"
#include "../getDir.h"
#include "InputHandle/mouseHandler.h"
#include "InputHandle/keyHandler.h"

#include "../Logic/Node.h"
#include "../Logic/Map.h"
#include "../Logic/Search_Algorithm/SearchAlgorithm.h"

const float squareVertices[] = {
		   -1.0f, -1.0f,
			1.0f, -1.0f,
			1.0f,  1.0f,
			1.0f,  1.0f,
		   -1.0f,  1.0f,
		   -1.0f, -1.0f,
};

// a class to handle the display graphics, as well as handle user inputs

class Graphics{
public:
	int windowWidth;
	int windowHeight;
	float addionalSpeed = 0;

	Graphics(Map* map,int width = 800, int height = 800);
	
	bool initialize();
	void run();

	~Graphics();
private:
	GLFWwindow* window;
	Map* worldMap;
	Shader* myShader;
	SearchAlgorithm search;
	int currSearchAlgo;

	MouseHandler mouseHandle;
	KeyHandler keyHandle;

	GLuint VAO = 0;
	GLuint VBO = 0;

	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	int FPS = 0;
	double lastFPSTime = 0.0f;
	double currentFPSTime = 0.0f;

	//--------functions/methods-------------------//

	bool createWindow();	
	void updateDeltaFrameTime();
	void printFPS();

	void drawGrid();
	void drawNode(float posX, float posY, float tileSizeX, float tileSizeY, Node* curr);

	void handleSoftInputs(); //can be blocked
	void handleHardInputs(); //aren't blocked, checked each frame
	Node* getNodeUnderMouse();

	void SetCallbackFunctions();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

