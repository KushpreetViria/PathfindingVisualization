#include "Graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#define SCR_WIDTH glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
#define SCR_HEIGHT glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
constexpr auto vertShaderPath = "\\Shaders\\vertShader.glsl";
constexpr auto fragShaderPath = "\\Shaders\\fragShader.glsl";

Graphics::Graphics(Map* map, int width, int height) : windowWidth(width), windowHeight(height),
    worldMap(map),window(nullptr),myShader(nullptr), mouseHandle(MouseHandler()),keyHandle(KeyHandler()){
}

bool Graphics::initialize() {
    if (!createWindow()) {
        std::cerr << "Error: failed to create glfw window" << std::endl;
        return false;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    SetCallbackFunctions();

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    myShader = new Shader(vertShaderPath, fragShaderPath);

    std::cout << "Initialized graphics Successfuly" << std::endl;

    return true;
}

void Graphics::run() {
    //bind square shape vertices to a buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);    

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInputs();

        glClearColor(0.0f,0.0f,0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader->use();
        glBindVertexArray(VAO);
        drawGrid();        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

//---------------------------------------------------------------------
//                      Private helper func
//---------------------------------------------------------------------

bool Graphics::createWindow() {
    if (glfwInit() != GLFW_TRUE) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PathFinder", glfwGetPrimaryMonitor(), nullptr);
    window = glfwCreateWindow(windowWidth, windowHeight, "PathFinder", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    return true;
}

void Graphics::handleInputs()
{    
    Node* theNode = getNodeUnderMouse();
    if(theNode != nullptr){
        if (mouseHandle.doubleClickHoldLeft) {
            theNode->setType(nodeType::WALKABLE);
        }else if (mouseHandle.singleClickkHoldLeft) {
            theNode->setType(nodeType::WALL);
        }else if (mouseHandle.doubleClickHoldRight) {
            theNode->setType(nodeType::END);
            worldMap->updateEndNode(theNode);
        }else if (mouseHandle.singleClickkHoldRight) {
            theNode->setType(nodeType::START);
            worldMap->updateStartNode(theNode);
        }
    }

    if (keyHandle.quit) {
        glfwSetWindowShouldClose(window, true);
    }else if (keyHandle.start) {
        worldMap->reset(false);
        keyHandle.start = false;
        bool result = SearchAlgorithm::simple_recursive_search(worldMap);        
        if(result) std::cout << "FOUND!" << std::endl;
        else std::cout << "FAIL!" << std::endl;
    }else if (keyHandle.reset) {
        keyHandle.reset = false;
        worldMap->reset(true);
    }
}

void Graphics::SetCallbackFunctions(){
    CallbackWrapper::SetGraphics(this);
    CallbackWrapper::SetMouseHandler(&mouseHandle);
    CallbackWrapper::SetKeyHandler(&keyHandle);

    glfwSetFramebufferSizeCallback(window, CallbackWrapper::FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, CallbackWrapper::MousePositionCallback);
    glfwSetMouseButtonCallback(window, CallbackWrapper::MouseBtnCallback);
    glfwSetKeyCallback(window, CallbackWrapper::KeyboardPressCallback);
}

//---------------------------------------------------------------------
//                      Define draw functions
//---------------------------------------------------------------------

void Graphics::drawGrid()
{
    int mapW = worldMap->getWidth();
    int mapH = worldMap->getHeight();
    Node** grid = worldMap->getNodes();

    //first calculate the size of a node (square) in both x and y
    float tileSizeW = (2.0f / (float)mapW);
    float tileSizeH = (2.0f / (float)mapH);

    glm::mat4 model = glm::mat4(1.0f);
    //dont need these, just set them to identity once
    myShader->setMat4("view", model);
    myShader->setMat4("projection", model);

    for (int row = 0; row < mapH; row++) {
        float vpPosY = (float)row * -tileSizeH + 1.0f;               //map its row in the 2d grid array to [-1,1] y viewport coords (flipped)
        for (int col = 0; col < mapW; col++) {
            Node* curr = &grid[row][col];
            
            float vpPosX = (float)col*tileSizeW - 1.0f;
            
            drawNode(vpPosX, vpPosY, tileSizeW, tileSizeH, curr);   //draw the node square
        }
    }
}

void Graphics::drawNode(float posX, float posY, float tileSizeX, float tileSizeY, Node* currNode)
{
    //draw a black box first, this is will look like an outline when the smaller box covers it
    glm::mat4 model = glm::mat4(1.0f);    

    //save these to avoid expensive divisions
    float halfTileX = tileSizeX / 2;
    float halfTileY = tileSizeY / 2;

    model = glm::translate(model, glm::vec3(posX + (halfTileX), posY-(halfTileY), 0.0f)); // do another scale, make it 5% smaller, this will show the black outline
    model = glm::scale(model, glm::vec3(0.95f* (halfTileX), 0.95f* (halfTileY), 1.0f));
    myShader->setMat4("model", model);

    //color the node based on its type
    glm::vec3 nodeCol;
    switch (currNode->getType()) {
    case nodeType::WALL:
        nodeCol = glm::vec3(0.85f, 0.1f, 0.1f);
        break;
    case nodeType::WALKABLE:
        nodeCol = glm::vec3(0.15f, 0.75f, 0.2f);
        break;
    case nodeType::VISITED:
        nodeCol = glm::vec3(0.8f, 0.85f, 0.2f);
        break;
    case nodeType::START:
        nodeCol = glm::vec3(0.0f, 0.2f, 0.2f);
        break;
    case nodeType::END:
        nodeCol = glm::vec3(0.0f, 0.45f, 0.9f);
        break;
    }
    myShader->setVec3f("myColor", nodeCol);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Node* Graphics::getNodeUnderMouse(){
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    if (!glfwGetWindowAttrib(window, GLFW_HOVERED) ||
        mouseHandle.mouseX < 0 || mouseHandle.mouseY < 0)
        return nullptr;

    int nodePixelWidth = win_width / worldMap->getWidth();
    int nodePixelHeight = win_height / worldMap->getHeight();

    //note: for large grid sizes (over million nodes), theres some index out bounds errors
    //when using int, so just use size_t. Its too slow on a million+ nodes to do anything anyways
    size_t colIndex = size_t(floor(mouseHandle.mouseX / nodePixelWidth));
    size_t rowIndex = size_t(floor(mouseHandle.mouseY / nodePixelHeight));

    Node* curr = &worldMap->getNodes()[rowIndex][colIndex];

    return curr;
}

//---------------------------------------------------------------------
//                     Define graphics callback functions
//---------------------------------------------------------------------
void Graphics::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//---------------------------------------------------------------------
//                    Set up callback wrapper
//---------------------------------------------------------------------
Graphics* Graphics::CallbackWrapper::graphics = nullptr;
MouseHandler* Graphics::CallbackWrapper::mouseHandle = nullptr;
KeyHandler* Graphics::CallbackWrapper::keyHandle = nullptr;

void Graphics::CallbackWrapper::FramebufferSizeCallback(GLFWwindow* window, int width, int height){
    graphics->framebuffer_size_callback(window, width, height);
}
void Graphics::CallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY){
    mouseHandle->mouse_pos_callback(window, positionX, positionY);
}
void Graphics::CallbackWrapper::KeyboardPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    keyHandle->key_press_callback(window, key, scancode, action, mods);
}
void Graphics::CallbackWrapper::MouseBtnCallback(GLFWwindow* window, int button, int action, int mods){
    mouseHandle->mouse_btn_press_callback(window, button, action, mods);
}

// set the handlers
void Graphics::CallbackWrapper::SetGraphics(Graphics* graphics) {
    CallbackWrapper::graphics = graphics;
}
void Graphics::CallbackWrapper::SetMouseHandler(MouseHandler* mh){
    CallbackWrapper::mouseHandle = mh;
}
void Graphics::CallbackWrapper::SetKeyHandler(KeyHandler* kh) {
    CallbackWrapper::keyHandle = kh;
}

Graphics::~Graphics()
{
    delete myShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if(window != nullptr) glfwDestroyWindow(window);
    glfwTerminate();
}