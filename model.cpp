//
// Created by Brett on 3/1/2018.
//

#include "model.h"
#include "overloading.h"
#include "GameState.h"

using namespace std;

// bind model data to VBO and VAO, set array attributes, set uniforms
void Model::bind(Shader shader, Matrix vMatrix, Matrix pMatrix, Matrix oMatrix) {
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertsSize * sizeof(float), verts, GL_STATIC_DRAW);

    // set vertex array object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // model matrix
    int modelLocation = glGetUniformLocation(shader.id(), "modelMatrix");
    glUniformMatrix4fv(modelLocation, 1, GL_TRUE, modelTransform.getMatrix());

    // group model matrix
    int groupLocation = glGetUniformLocation(shader.id(), "groupMatrix");
    glUniformMatrix4fv(groupLocation, 1, GL_TRUE, groupTransform.getMatrix());

    // view matrix
    int viewLocation = glGetUniformLocation(shader.id(), "viewMatrix");
    glUniformMatrix4fv(viewLocation, 1, GL_TRUE, vMatrix.getMatrix());

    // projection matrix
    int projectionLocation = glGetUniformLocation(shader.id(), "projectionMatrix");

    // perspective
    if(GameState::persp){
        glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, pMatrix.getMatrix());
    }
        // orthagonol
    else{
        glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, oMatrix.getMatrix());
    }
}

// use model's group's transform as current state of program
void Model::setGameStateToGroupModel(){
    GameState::rx = grx;
    GameState::ry = gry;
    GameState::rz = grz;
    GameState::sx = gsx;
    GameState::sy = gsy;
    GameState::sz = gsz;
    GameState::tx = gtx;
    GameState::ty = gty;
    GameState::tz = gtz;
}

// set group transformation matrix
void Model::setGroupModel(float rx, float ry, float rz,float sx,float sy,float sz,float tx,float ty,float tz){
    //cout << "setting group model" << endl;
    this -> grx = rx;
    this -> gry = ry;
    this -> grz = rz;
    this -> gsx = sx;
    this -> gsy = sy;
    this -> gsz = sz;
    this -> gtx = tx;
    this -> gty = ty;
    this -> gtz = tz;
    // initialize model matrix transformation objects
    RotateMatrix rzMatrix = RotateMatrix(4,4,0,0,0);
    RotateMatrix rxMatrix = RotateMatrix(4,4,0,0,0);
    RotateMatrix ryMatrix = RotateMatrix(4,4,0,0,0);
    rxMatrix.setXYZ(grx,gry,grz);
    ryMatrix.setXYZ(grx,gry,grz);
    rzMatrix.setXYZ(grx,gry,grz);
    rzMatrix.createZMatrix(0);
    rxMatrix.createXMatrix(0);
    ryMatrix.createYMatrix(0);
    Matrix rxyzMatrix = rxMatrix * ryMatrix * rzMatrix; // rotate

    TranslateMatrix tMatrix = TranslateMatrix(4,4,0,0,0);
    tMatrix.setXYZ(gtx,gty,gtz); // translate

    ScaleMatrix sMatrix = ScaleMatrix(4,4,1,1,1);
    sMatrix.setXYZ(gsx,gsy,gsz); // scale

    // final model matrix
    groupTransform = tMatrix * rxyzMatrix * sMatrix;
}

// use model's transform as current state of program
void Model::setGameStateToModel() {
    GameState::rx = rx;
    GameState::ry = ry;
    GameState::rz = rz;
    GameState::sx = sx;
    GameState::sy = sy;
    GameState::sz = sz;
    GameState::tx = tx;
    GameState::ty = ty;
    GameState::tz = tz;
}

// set model transformation matrix
void Model::setModel(float rx, float ry, float rz,float sx,float sy,float sz,float tx,float ty,float tz) {
    if (GameState::mode == group){
        //cout << "setting model" << endl;
    }
    this -> rx = rx;
    this -> ry = ry;
    this -> rz = rz;
    this -> sx = sx;
    this -> sy = sy;
    this -> sz = sz;
    this -> tx = tx;
    this -> ty = ty;
    this -> tz = tz;
    // initialize model matrix transformation objects
    RotateMatrix rzMatrix = RotateMatrix(4,4,0,0,0);
    RotateMatrix rxMatrix = RotateMatrix(4,4,0,0,0);
    RotateMatrix ryMatrix = RotateMatrix(4,4,0,0,0);
    rxMatrix.setXYZ(rx,ry,rz);
    ryMatrix.setXYZ(rx,ry,rz);
    rzMatrix.setXYZ(rx,ry,rz);
    rzMatrix.createZMatrix(0);
    rxMatrix.createXMatrix(0);
    ryMatrix.createYMatrix(0);
    Matrix rxyzMatrix = rxMatrix * ryMatrix * rzMatrix; // rotate

    TranslateMatrix tMatrix = TranslateMatrix(4,4,0,0,0);
    tMatrix.setXYZ(tx,ty,tz); // translate

    ScaleMatrix sMatrix = ScaleMatrix(4,4,1,1,1);
    sMatrix.setXYZ(sx,sy,sz); // scale

    // final model matrix
    modelTransform = tMatrix * rxyzMatrix * sMatrix;
}

// draw model
void Model::display() {
    glDrawArrays(GL_TRIANGLES, 0, vertsSize * sizeof(float));
}