// Brett Layman
// 2/21/2018.

// 3 dimensional vector implementation
#include <iostream>
#include "Vector3.h"
#include <math.h>

// return normalized version of vector
Vector3 Vector3::normalize(){
    float length = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
    Vector3* normalized = new Vector3(xyz[0]/length, xyz[1]/length, xyz[2]/length);
    return *normalized;
}

// take cross product of vector, and another vector
Vector3 Vector3::cross(Vector3 other) {
    float x = xyz[1] * other.xyz[2] - xyz[2] * other.xyz[1];
    float y = xyz[2] * other.xyz[0] - xyz[0] * other.xyz[2];
    float z = xyz[0] * other.xyz[1] - xyz[1] * other.xyz[0];
    Vector3 crossVec = Vector3(x,y,z);
    return crossVec;
}

float Vector3::dot(Vector3 other) {
    return xyz[0] * other.xyz[0] + xyz[1] * other.xyz[1] + xyz[2] * other.xyz[2];
}

float Vector3::magnitude() {
    return sqrt(pow(xyz[0],2) + pow(xyz[1],2) + pow(xyz[2],2) );
}

// print vector elements
void Vector3::print() {
    for (int i = 0; i < 3; ++i) {
        std::cout << xyz[i] << ", ";
    }
    std::cout << std::endl;
}

