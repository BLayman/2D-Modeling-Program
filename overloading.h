//
// Created by Brett on 3/1/2018.

// operator overloading code

#include "Matrix.h"
#include "Vector3.h"

#ifndef GLFW_EXAMPLE_OVERLOADING_H
#define GLFW_EXAMPLE_OVERLOADING_H


// matrix multiplication via operator overloading
Matrix operator * (const Matrix& m1, const Matrix& m2);

// vector subtraction
Vector3 operator - (const Vector3& v1, const Vector3& v2);

// vector scalar multiplication
Vector3 operator * (const float scalar, const Vector3& v1);

// matrix vector multiplication
Vector3 operator * (const Matrix& matrix, const Vector3& vector);

#endif //GLFW_EXAMPLE_OVERLOADING_H