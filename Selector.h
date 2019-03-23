//
// Created by Brett on 3/7/2018.
//

#include "Vector3.h"
#include "ModelHandler.h"
#include "overloading.h"

#ifndef PROJECT_1_SELECTOR_H
#define PROJECT_1_SELECTOR_H

#endif //PROJECT_1_SELECTOR_H


// class for selecting models
class Selector{
public:

    // helper functions
    double max(double a, double b){
        if(a > b){return a;}
        else{return b;}
    }

    double min(double a, double b){
        if(a < b){return a;}
        else{return b;}
    }

    bool checkIfInside(Vector3 location, double startX, double endX, double startY, double endY){
        if(location.xyz[0] < max(startX, endX) &&
           location.xyz[0] > min(startX, endX) &&
           location.xyz[1] < max(startY, endY) &&
           location.xyz[1] > min(startY, endY)){
            cout << "inside" << endl;
            return true;
        }
        else{
            return false;
        }
    }


    // find what models are inside of selection box
    void findSelected(ModelHandler& modelHandler, Matrix negCameraPos, Matrix pMatrix, float startX, float startY,float endX, float endY){
        GameState::selected = false;
        bool foundOne = false;

        // for each model, see if it's inside
        for(Model* model : modelHandler.models){
            Matrix modelTransform = model->modelTransform;
            Matrix groupModelTransform = model->groupTransform;
            Vector3 point = Vector3(model->verts[0],model->verts[1],model->verts[2]);
            Vector3 location = pMatrix * (negCameraPos * (groupModelTransform * (modelTransform * point)));
            location.print();
            bool inside = checkIfInside(location, startX, endX, startY, endY);
            model->selected = inside;

            // if it's inside, set the game state to that model or group of models
            if(inside){
                foundOne = true;
                if(GameState::mode == modify){
                    model->setGameStateToModel();
                    cout << "in modify mode";
                }
                else if (GameState::mode == group){
                    cout << "in group mode";
                    model->setGameStateToGroupModel();
                }
            }
        }
        // set flags
        if(foundOne){GameState::foundSelected = true;}
        else{GameState::foundSelected = false;}
    }

    // get selection box shape
    float* getBox(float x, float y, float startX, float startY){
        float verts[] = {
                startX, startY, 0.0f,1.0f,1.0f,1.0f,
                startX, y, 0.0f,1.0f,1.0f,1.0f,
                startX + .001f, y, 0.0f,1.0f,1.0f,1.0f,

                startX, startY, 0.0f,1.0f,1.0f,1.0f,
                startX + .001f, startY, 0.0f,1.0f,1.0f,1.0f,
                startX + .001f, y, 0.0f,1.0f,1.0f,1.0f,

                startX, startY, 0.0f,1.0f,1.0f,1.0f,
                startX, startY + .001f, 0.0f,1.0f,1.0f,1.0f,
                x, startY, 0.0f,1.0f,1.0f,1.0f,

                startX, startY + .001f, 0.0f,1.0f,1.0f,1.0f,
                x, startY, 0.0f,1.0f,1.0f,1.0f,
                x, startY + .001f, 0.0f,1.0f,1.0f,1.0f,

                x - .001f, y, 0.0f,1.0f,1.0f,1.0f,
                x, startY, 0.0f,1.0f,1.0f,1.0f,
                x - .001f, startY, 0.0f,1.0f,1.0f,1.0f,

                x, y, 0.0f,1.0f,1.0f,1.0f,
                x - .001f, y, 0.0f,1.0f,1.0f,1.0f,
                x, startY + .001f, 0.0f,1.0f,1.0f,1.0f,

                x, y, 0.0f,1.0f,1.0f,1.0f,
                x, y + .001f, 0.0f,1.0f,1.0f,1.0f,
                startX, y + .001f, 0.0f,1.0f,1.0f,1.0f,

                x, y, 0.0f,1.0f,1.0f,1.0f,
                startX, y, 0.0f,1.0f,1.0f,1.0f,
                startX, y + .001f, 0.0f,1.0f,1.0f,1.0f,

        };
        float* heapVerts = new float[sizeof(verts)/ sizeof(float)];
        copy(verts,verts + sizeof(verts)/ sizeof(float),heapVerts);
        return heapVerts;

    }
};