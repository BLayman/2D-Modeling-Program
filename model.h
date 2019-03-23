//
// Created by Brett on 3/1/2018.
//
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include <ext.hpp>
*/

#include <csci441/shader.h>
#include "Matrix.h"
#include "Vector3.h"


#ifndef GLFW_EXAMPLE_MODEL_H
#define GLFW_EXAMPLE_MODEL_H

// class for storing information about a 2D model (vertices, transforms, etc)
class Model {
public:
    bool selected;
    float* verts;
    Matrix modelTransform;
    Matrix groupTransform;
    int vertsSize;
    float rx;
    float ry;
    float rz;
    float sx;
    float sy;
    float sz;
    float tx;
    float ty;
    float tz;

    float grx;
    float gry;
    float grz;
    float gsx;
    float gsy;
    float gsz;
    float gtx;
    float gty;
    float gtz;

    Model(float* _verts, int _vertsSize): modelTransform(4,4), groupTransform(4,4){
        modelTransform = Matrix(4,4);
        groupTransform = Matrix(4,4);
        verts = _verts;
        vertsSize = _vertsSize;
        setModel(0,0,0,1,1,1,0,0,0);
        setGroupModel(0,0,0,1,1,1,0,0,0);
        selected = false;
    }

    void bind(Shader shader, Matrix vMatrix, Matrix pMatrix, Matrix oMatrix);

    void setModel(float rx, float ry, float rz,float sx,float sy,float sz,float tx,float ty,float tz);

    void setGroupModel(float rx, float ry, float rz,float sx,float sy,float sz,float tx,float ty,float tz);

    void setGameStateToModel();

    void setGameStateToGroupModel();

    void display();
};


#endif //GLFW_EXAMPLE_MODEL_H
