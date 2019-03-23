// Brett Layman
// 2/21/2018

#include <math.h>
#ifndef GLFW_EXAMPLE_VECTOR3_H
#define GLFW_EXAMPLE_VECTOR3_H


// class to represent a 3 dimensional vector
class Vector3 {
public:
    float* xyz;

    Vector3(float _x,float _y,float _z){
        xyz = new float[3];
        xyz[0] = _x;
        xyz[1] = _y;
        xyz[2] = _z;
        xyz[3] = 1;
    }

    Vector3 normalize();
    Vector3 cross(Vector3 other);
    float dot(Vector3);
    float magnitude();
    void print();

};


#endif //GLFW_EXAMPLE_VECTOR3_H
