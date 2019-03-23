//
// Created by Brett on 3/9/2018.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <list>
#include <math.h>

#include "Vector3.h"
#include "GameState.h"


using namespace std;

#ifndef PROJECT_1_CUSTOMSHAPE_H

#define PROJECT_1_CUSTOMSHAPE_H


// class for user defined shape creation
class CustomShape{
public:
    list<float*> points;
    list<float*> verts;
    static CustomShape* currentCustom;


    static void resetShape(){
        currentCustom = new CustomShape();
    }

    // add vertex to shape
    void addPoint(double x, double y){
        cout << "added point" << endl;
        // convert to world coordinates by reversing orthographic projection
        float l = -(GameState::orthoWidth/2);
        float r = (GameState::orthoWidth/2);
        float b = -(GameState::orthoHeight/2);
        float t = (GameState::orthoHeight/2);
        float xOrth = ((x + 1) * (r - l) + 2*l)/ 2;
        float yOrth = ((y + 1) * (t - b) + 2*b)/ 2;
        // create and add point
        float * point = new float[6];
        point[0] = xOrth + GameState::vx;
        point[1] = yOrth + GameState::vy;
        point[2] = 0;
        point[3] = 1;
        point[4] = 0;
        point[5] = 0;
        points.push_back(point);
    }

    bool checkIfConvex(float* first, float* middle, float* last){

        float ax = middle[0] - first[0];
        float ay = middle[1] - first[1];

        float bx = middle[0] - last[0];
        float by = middle[1] - last[1];

        Vector3 a = Vector3(ax,ay,0);
        Vector3 b = Vector3(bx,by,0);

        float aDotB = a.dot(b);
        float magA = a.magnitude();
        float magB = b.magnitude();
        float angle = acos((double)(aDotB / (magA * magB)));
        cout << "angle: " << angle << endl;
        if(angle <= M_PI){
            return true;
        }
        else{
            return false;
        }
    }

    void earClipping() {
        // while there are 3 or more points left
        while (points.size() >= 3) {
            // iterate over points
            list<float *>::iterator iterator;
            for (iterator = points.begin(); std::next(iterator,2) != points.end() && std::next(iterator,1) != points.end(); ++iterator) {
                auto middle = std::next(iterator, 1);
                auto last = std::next(iterator, 2);
                bool isConvex = checkIfConvex(*iterator, *middle, *last);
                if (isConvex) {
                    verts.push_back(*iterator);
                    verts.push_back(*middle);
                    verts.push_back(*last);
                    points.remove(*middle);

                }
            }
        }
    }

    // build shape from vertices (incomplete)
    float* buildShape(int* lenPtr){
        cout << points.size() << endl;
        int length = verts.size() * 6;
        *lenPtr = length;
        float* shape = new float[length];
        int k = 0;
        for(float* vert : verts){
            for (int i = 0; i < 6; ++i) {
                shape[k] = vert[i];
                k++;
            }
        }
        return shape;
    }

};




#endif //PROJECT_1_CUSTOMSHAPE_H



