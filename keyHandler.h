//
// Created by Brett on 3/1/2018.
//
#include <iostream>
#include "ModelHandler.h"

#ifndef GLFW_EXAMPLE_KEYHANDLER_H
#define GLFW_EXAMPLE_KEYHANDLER_H

using namespace std;

// for managing key callbacks
class KeyHandler{
public:
    static void handlePress(int key, int action, GLFWwindow* window);
    static void handlePressed(GLFWwindow* window);
};

// handle key presses
void KeyHandler::handlePress(int key, int action, GLFWwindow* window){

    // listen for object creation in stamp mode
    if (GameState::mode == stamp){
        if (key == GLFW_KEY_T && action == GLFW_PRESS) {
            GameState::createTriangle = true;
        }
        if (key == GLFW_KEY_C && action == GLFW_PRESS) {
            GameState::createCircle = true;
        }
        if (key == GLFW_KEY_S && action == GLFW_PRESS) {
            GameState::createSquare = true;
        }
    }
    // changing game mode
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        GameState::mode = view;
        GameState::changedMode = true;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        GameState::mode = stamp;
        GameState::changedMode = true;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        GameState::mode = modify;
        GameState::changedMode = true;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        GameState::mode = group;
        GameState::changedMode = true;
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        GameState::mode = custom;
        GameState::changedMode = true;
    }
    // exit program
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    /*
    if (key == GLFW_KEY_SLASH && action == GLFW_PRESS){
        if(GameState::persp){ GameState::persp = false; }
        else{ GameState::persp = true; }
    }
     */
    // set color
    if (GameState::mode == modify || GameState::mode == group){
        if (key == GLFW_KEY_R && action== GLFW_PRESS){ GameState::setColor = red; }
        if (key == GLFW_KEY_G && action== GLFW_PRESS){ GameState::setColor = green; }
        if (key == GLFW_KEY_B && action== GLFW_PRESS){ GameState::setColor = blue; }
    }
    // enter to draw custom shape
    if (GameState::mode == custom){
        if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
            GameState::createCustom = true;
        }
    }
}

// listen for keys being held down
void KeyHandler::handlePressed(GLFWwindow* window){
    // transformation keys
    if (GameState::mode == stamp || ((GameState::mode == modify || GameState::mode == group) && GameState::foundSelected)){
        // up down
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){ GameState::ty += .1;}
        if (glfwGetKey(window,GLFW_KEY_DOWN ) == GLFW_PRESS){ GameState::ty -= .1;}

        // left right
        if (glfwGetKey(window,GLFW_KEY_LEFT ) == GLFW_PRESS){ GameState::tx -= .1; }
        if (glfwGetKey(window,GLFW_KEY_RIGHT ) == GLFW_PRESS){ GameState::tx += .1; }


        // forward back
        if (glfwGetKey(window,GLFW_KEY_COMMA ) == GLFW_PRESS){ GameState::tz -= .5; }
        if (glfwGetKey(window,GLFW_KEY_PERIOD ) == GLFW_PRESS){ GameState::tz += .5;  }

        // plus minus
        if (glfwGetKey(window,GLFW_KEY_EQUAL ) == GLFW_PRESS){ GameState::sx += .25; GameState::sy += .25; GameState::sz += .25; }
        if (glfwGetKey(window,GLFW_KEY_MINUS ) == GLFW_PRESS && GameState::sx > 0){ GameState::sx -= .25; GameState::sy -= .25; GameState::sz -= .25; }

        // o p
        if (glfwGetKey(window,GLFW_KEY_O ) == GLFW_PRESS && GameState::sx > 0){ GameState::sx -= .25; }
        if (glfwGetKey(window,GLFW_KEY_P ) == GLFW_PRESS){ GameState::sx += .25;}

        // u i
        if (glfwGetKey(window,GLFW_KEY_U ) == GLFW_PRESS && GameState::sy > 0){ GameState::sy -= .25;; }
        if (glfwGetKey(window,GLFW_KEY_I ) == GLFW_PRESS){ GameState::sy += .25;; }

        // lb rb
        if (glfwGetKey(window,GLFW_KEY_LEFT_BRACKET ) == GLFW_PRESS){ GameState::rz += 1; }
        if (glfwGetKey(window,GLFW_KEY_RIGHT_BRACKET ) == GLFW_PRESS){ GameState::rz -= 1; }
    }
    // changes to view
    else if(GameState::mode == view){
        if (glfwGetKey(window,GLFW_KEY_EQUAL ) == GLFW_PRESS && GameState::orthoHeight > 0){
            GameState::orthoWidth *= .9;
            GameState::orthoHeight *= .9;
        }
        if (glfwGetKey(window,GLFW_KEY_MINUS ) == GLFW_PRESS ){
            GameState::orthoWidth *= 1.1;
            GameState::orthoHeight *= 1.1;
        }
    }


    // w, s
    /*
    if (glfwGetKey(window,GLFW_KEY_W ) == GLFW_PRESS && GameState::vy > -20){GameState::vy -= .5; }
    if (glfwGetKey(window,GLFW_KEY_S ) == GLFW_PRESS && GameState::vy < 20){ GameState::vy += .5;  }
    */

}

#endif //GLFW_EXAMPLE_KEYHANDLER_H