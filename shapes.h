//
// Created by Brett on 3/1/2018.
//

#ifndef GLFW_EXAMPLE_SHAPES_H
#define GLFW_EXAMPLE_SHAPES_H
#define _USE_MATH_DEFINES
#include<math.h>
#include <iostream>
using namespace std;


// class for storing shapes
class Shapes{
public:
    // square
    static float* square(float r, float g, float b){
        float square[] = {
                0.5f,  0.5f, 0.0f, r, g, b,
                0.5f, -0.5f, 0.0f, r, g, b,
                -0.5f,  0.5f, 0.0f, r, g, b,

                0.5f, -0.5f, 0.0f, r, g, b,
                -0.5f, -0.5f, 0.0f, r, g, b,
                -0.5f,  0.5f, 0.0f, r, g, b,
        };
        float* rSquare = new float[sizeof(square)/ sizeof(float)];
        copy(square,square + sizeof(square)/ sizeof(float),rSquare);
        return rSquare;
    }

    // triangle
    static float* triangle(float r, float g, float b){
        float triangle[] = {
                0.5f,  0.5f, 0.0f, r, g, b,
                0.5f, -0.5f, 0.0f, r, g, b,
                -0.5f,  0.5f, 0.0f, r, g, b,
        };
        float* rtriangle = new float[sizeof(triangle)/ sizeof(float)];
        copy(triangle,triangle + sizeof(triangle)/sizeof(float),rtriangle);
        return rtriangle;
    }

    // circle
    static float* circle(int edges, float r, float g, float b){
        int iterCount = 0;
        int vertsIndex = 0;
        float* verts = new float[edges * 18];
        float circleClose1[3];
        float circleClose2[3];
        circleClose1[2] = 0;
        circleClose2[2] = 0;
        float centerClose[] = {0,0,0};

        for (double i = 0; i <= M_PI * 2 + .00001; ) {
            if(iterCount == 0){
                circleClose1[0] = cos(i);
                circleClose1[1] = sin(i);
                i += M_PI * 2/edges;
            }
            else if (iterCount == 1){
                circleClose2[0] = cos(i);
                circleClose2[1] = sin(i);

                float triangle[] = {
                        circleClose1[0], circleClose1[1], circleClose1[2], r,g,b,
                        circleClose2[0], circleClose2[1], circleClose2[2], r,g,b,
                        centerClose[0], centerClose[1], centerClose[2], r,g,b,
                };

                for (int j = 0; j < 18; ++j) {
                    verts[vertsIndex] = triangle[j];
                    vertsIndex++;
                }
                iterCount = -1;
            }
            iterCount++;
        }
        for (int k = 0; k < edges * 18; ++k) {
            cout << k << " " << verts[k] << endl;
        }
        return verts;
    }
};



#endif //GLFW_EXAMPLE_SHAPES_H
