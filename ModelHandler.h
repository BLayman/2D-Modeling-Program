//
// Created by Brett on 3/3/2018.
//
#include "model.h"
#include "shapes.h"
#include "GameState.h"
#include "CustomShape.h"
#include <list>

#ifndef PROJECT_1_SHAPEHANDLER_H
#define PROJECT_1_SHAPEHANDLER_H

// class for managing models

class ModelHandler{
public:
    std::list<Model*> models; // list of all models

    /* model creation methods */
    void createTriangle(){
        float* triangleVerts = Shapes::triangle(0,1,0);
        Model* triangleModel = new Model(triangleVerts, 18);
        (*triangleModel).setGameStateToModel();
        models.push_back(triangleModel);
    }

    void createSquare(){
        float* squareVerts = Shapes::square(0,0,1);
        Model* squareModel = new Model(squareVerts, 36);
        (*squareModel).setGameStateToModel();
        models.push_back(squareModel);
    }

    void createCircle(){
        float* circleVerts = Shapes::circle(10,1,0,0);
        Model* circleModel = new Model(circleVerts, 180);
        (*circleModel).setGameStateToModel();
        models.push_back(circleModel);
    }

    void createCustom(){
        int length;
        int* lenPtr = &length;
        CustomShape::currentCustom->earClipping();
        float* customShape = CustomShape::currentCustom->buildShape(lenPtr);
        Model* customModel = new Model(customShape, length);
        models.push_back(customModel);
        CustomShape::resetShape();
    }

    // re-create model with new color
    void changeColor(Model* model){
        int r = 0;
        int g = 0;
        int b = 0;
        switch(GameState::setColor){
            case red:
                r = 1;
                break;
            case green:
                g = 1;
                break;
            case blue:
                b = 1;
                break;
        }
        float* verts;
        switch(model->vertsSize){
            case 18:
                verts = Shapes::triangle(r,g,b);
                break;
            case 36:
                verts = Shapes::square(r,g,b);
                break;
            case 180:
                verts = Shapes::circle(10,r,g,b);
                break;
        }
        model->verts = verts;
    }

    // calls creation methods
    void handleObjectCreation(){
        if(GameState::createTriangle){
            createTriangle();
            GameState::createTriangle = false;
        }
        if(GameState::createSquare){
            createSquare();
            GameState::createSquare = false;
        }
        if(GameState::createCircle){
            createCircle();
            GameState::createCircle = false;
        }
        if(GameState::createCustom){
            createCustom();
            GameState::createCustom = false;
        }
    }

    // display all models
    void displayModels(Shader shader, Matrix vMatrix, Matrix pMatrix, Matrix oMatrix){
        for(Model* model : models){
            model->bind(shader,vMatrix, pMatrix,oMatrix);
            model->display();
        }
    }

    // set model transformation matrix of most recently created model (for stamp mode)
    void setLastTransform(){
        (*models.back()).setModel(GameState::rx, GameState::ry, GameState::rz,
                               GameState::sx,GameState::sy, GameState::sz,
                               GameState::tx, GameState::ty, GameState::tz);
    }

    // transform selected models
    void setSelectedTransform(){
        for(Model* model: models){
            if(model->selected){
                if(GameState::setColor != dont){
                    changeColor(model);
                    GameState::setColor = dont;
                }
                model->setModel(GameState::rx, GameState::ry, GameState::rz,
                                  GameState::sx,GameState::sy, GameState::sz,
                                  GameState::tx, GameState::ty, GameState::tz);
            }
        }
    }

    // transform selected group
    void setSelectedGroupTransform(){
        for(Model* model: models){
            if(model->selected){
                if(GameState::setColor != dont){
                    changeColor(model);
                }
                model->setGroupModel(GameState::rx, GameState::ry, GameState::rz,
                                GameState::sx,GameState::sy, GameState::sz,
                                GameState::tx, GameState::ty, GameState::tz);
            }
        }
        GameState::setColor = dont;
    }

    // deselect models
    void deselectAllModels() {
        for (Model *model: models) {
            if (model->selected) {
                model->selected = false;
            }
        }
    }

};

#endif //PROJECT_1_SHAPEHANDLER_H
