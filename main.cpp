// Brett Layman
// 2/21/2018

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include "GameState.h"
#include "Matrix.h"
#include "keyHandler.h"
#include "Selector.h"

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1440;

using namespace std;


// handle key presses
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeyHandler::handlePress(key,action,window);
}

// convert to normalized device coordinates from window coordinates
void convertToNDC(double screenX, double screenY, float width, float height,float& NDCX,float& NDCY){
    NDCX = -1 + screenX * (2/width);
    NDCY = 1 - screenY * (2/height);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods){
    // mouse clicked
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ){

        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        // set start position of mouse
        GameState::startDragX = x;
        GameState::startDragY = y;
        GameState::mouseDragged = true;
        // if making custom shape, add coordinates as new vertex in shape
        if(GameState::mode == custom){
            float x;
            float y;
            convertToNDC(GameState::startDragX, GameState::startDragY, SCREEN_WIDTH, SCREEN_HEIGHT, x, y);
            CustomShape::currentCustom->addPoint(x,y);
        }
    }
        // mouse released
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        GameState::mouseDragged = false;
        // store previous view location
        GameState::vyPrev = GameState::vy;
        GameState::vxPrev = GameState::vx;
        // get mouse release location
        glfwGetCursorPos(window, &GameState::finishDragX, &GameState::finishDragY);
        GameState::selected = true;
    }
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);


    if((float)width/height > (float)SCREEN_WIDTH/SCREEN_HEIGHT){
        GameState::orthoWidth = (GameState::orthoHeight * ((float)SCREEN_WIDTH/SCREEN_HEIGHT));
    }
    else if((float)width/height < (float)SCREEN_WIDTH/SCREEN_HEIGHT){
        GameState::orthoHeight = (GameState::orthoWidth * ((float)SCREEN_HEIGHT/SCREEN_WIDTH));
    }

    SCREEN_HEIGHT = height;
    SCREEN_WIDTH = width;
}


void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}


// translate view using mouse drag in view mode
void translateView(GLFWwindow* window){
    double mx;
    double my;
    glfwGetCursorPos(window, &mx, &my);
    // continuously change view based on difference in mouse position
    GameState::vx = .02 * (GameState::startDragX - mx) + GameState::vxPrev;
    GameState::vy = .02 * (my - GameState::startDragY) + GameState::vyPrev;
}



/** start main **/
int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lab 4", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");


    /** My code starts here **/

    // set callback for keyboard input
    glfwSetKeyCallback(window, key_callback);
    // mouse input callback
    glfwSetMouseButtonCallback(window, mouseCallback);

    // for keeping track of multiple models
    ModelHandler modelHandler = ModelHandler();

    // initialize view matrix and camera position
    TranslateMatrix negCameraPos = TranslateMatrix(4,4,0,0,0);
    Matrix vMatrix = Matrix(4,4);

    // orthagonal
    OrthoMatrix oMatrix = OrthoMatrix(4,4);
    oMatrix.createMatrix( -(GameState::orthoWidth/2), (GameState::orthoWidth/2),
                          -(GameState::orthoHeight/2), (GameState::orthoHeight/2), 0.0f, 50.0f);

    // perspective
    PerspMatrix pMatrix = PerspMatrix(4,4);
    pMatrix.createMatrix(8.0f,SCREEN_HEIGHT/SCREEN_WIDTH,2.0f,100.0f);

    // class for selecting models on screen
    Selector selector = Selector();

    // use z-buffering
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        // process keys being pressed
        KeyHandler::handlePressed(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        // translate to negative camera position
        negCameraPos.setXYZ(-GameState::vx,-GameState::vy,-GameState::vz);

        // set orthographic bounding box
        oMatrix.createMatrix( -(GameState::orthoWidth/2), (GameState::orthoWidth/2),
                              -(GameState::orthoHeight/2), (GameState::orthoHeight/2), 0.0f, 50.0f);

        // depending on what mode the user is in
        switch(GameState::mode){
            // view mode: for navigating space
            case view:
                if (GameState::changedMode){
                    GameState::changedMode = false;
                    modelHandler.deselectAllModels();
                }
                // move view when mouse dragged
                if(GameState::mouseDragged){
                    translateView(window);
                    // set new cameraPosition
                    negCameraPos.setXYZ(-GameState::vx,-GameState::vy,-GameState::vz);
                }
                // reset orthographic bounding box
                oMatrix.createMatrix( -(GameState::orthoWidth/2), (GameState::orthoWidth/2),
                                      -(GameState::orthoHeight/2), (GameState::orthoHeight/2), 0.0f, 50.0f);
                break;
                // mode for creating new primitives
            case stamp:
                // if just changed to stamp mode
                if(GameState::changedMode){
                    modelHandler.deselectAllModels();
                    if(!modelHandler.models.empty()) {
                        modelHandler.models.back()->setGameStateToModel();
                    }
                    GameState::changedMode = false;
                }
                // create any new objects
                modelHandler.handleObjectCreation();
                if(!modelHandler.models.empty()) {
                    modelHandler.setLastTransform();
                }
                break;
                // shape modifying mode
            case modify:
                // if just changed to modify mode
                if (GameState::changedMode){
                    GameState::changedMode = false;
                    modelHandler.deselectAllModels();
                    GameState::selected = false;
                }
                // if a selection area has been drawn, check for objects in that area using the selector
                if(GameState::selected){
                    float startX;
                    float startY;
                    convertToNDC(GameState::startDragX, GameState::startDragY, SCREEN_WIDTH, SCREEN_HEIGHT, startX, startY);
                    float endX;
                    float endY;
                    convertToNDC(GameState::finishDragX, GameState::finishDragY, SCREEN_WIDTH, SCREEN_HEIGHT, endX, endY);
                    selector.findSelected(modelHandler, negCameraPos, oMatrix, startX, startY,endX,endY);
                }
                // set model transform for selected object
                if(!modelHandler.models.empty()) {
                    modelHandler.setSelectedTransform();
                }
                break;
                // mode for grouping shapes together
            case group:
                // if just changed to group mode
                if (GameState::changedMode){
                    GameState::changedMode = false;
                    modelHandler.deselectAllModels();
                    GameState::selected = false;
                }
                // if a selection area has been drawn, check for objects in that area using the selector
                if(GameState::selected){
                    float startX;
                    float startY;
                    convertToNDC(GameState::startDragX, GameState::startDragY, SCREEN_WIDTH, SCREEN_HEIGHT, startX, startY);
                    float endX;
                    float endY;
                    convertToNDC(GameState::finishDragX, GameState::finishDragY, SCREEN_WIDTH, SCREEN_HEIGHT, endX, endY);
                    selector.findSelected(modelHandler, negCameraPos, oMatrix, startX, startY,endX,endY);
                }
                // set model transform for group of objects
                if(!modelHandler.models.empty()) {
                    modelHandler.setSelectedGroupTransform();
                }
                break;
            case custom:
                // create any objects the user has drawn
                modelHandler.handleObjectCreation();
                break;
        }

        // final view matrix
        vMatrix = negCameraPos;
        // if there are models to display, then update and display them
        if(!modelHandler.models.empty()){
            modelHandler.displayModels(shader,vMatrix,pMatrix,oMatrix);
        }

        // draw selection box for modify and group modes
        if(GameState::mouseDragged && (GameState::mode == modify || GameState::mode == group)){
            double winx;
            double winy;
            float x;
            float y;
            float startX;
            float startY;
            glfwGetCursorPos(window, &winx, &winy);
            convertToNDC(winx, winy, SCREEN_WIDTH, SCREEN_HEIGHT, x, y);
            convertToNDC(GameState::startDragX, GameState::startDragY, SCREEN_WIDTH, SCREEN_HEIGHT, startX, startY);

            float* verts = selector.getBox(x,y,startX,startY);
            Model* box = new Model(verts,144);
            IdentityMatrix identity = IdentityMatrix(4,4);
            box->bind(shader,identity,identity,identity);
            box->display();
            delete[] verts;
            delete (box);
        }

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
