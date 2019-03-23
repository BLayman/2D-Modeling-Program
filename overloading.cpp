//
// Created by Brett on 3/1/2018.
//

#include "Matrix.h"
#include "Vector3.h"

// matrix multiplication via operator overloading
Matrix operator * (const Matrix& m1, const Matrix& m2) {
    // get data from input Matrices
    float* m1Array = m1.getMatrix();
    float* m2Array = m2.getMatrix();
    int size = m1.rows * m2.columns;
    // calculate coordinates of new matrix
    float* newArray = new float[size];
    int i = 0;
    int m = 0;
    while (i < m1.rows){
        for (int j = 0; j < m2.columns; ++j) {
            float sum = 0;
            for (int k = 0; k < m2.rows; ++k) {
                int m1Index = (i * m1.columns) + k;
                int m2Index = (k * m2.columns) + j;
                sum += m1Array[m1Index] * m2Array[m2Index];
            }
            newArray[m] = sum;
            m++;
        }
        i++;
    }
    // assign data to new Matrix and return it
    Matrix mat = Matrix(m1.rows, m2.columns);
    mat.createMatrix(newArray);
	delete[] newArray;
    return mat;
}

// matrix vector multiplication
Vector3 operator * (const Matrix& matrix, const Vector3& vector){
    Vector3 product = Vector3(0,0,0);
    for (int i = 0; i < matrix.rows; ++i) {
        float sum = 0;
        for (int j = 0; j < matrix.columns; ++j) {
            sum += matrix.getMatrix()[(i * matrix.columns) + j] * vector.xyz[j];
        }
        product.xyz[i] = sum;
    }
    return product;
}

// vector subtraction
Vector3 operator - (const Vector3& v1, const Vector3& v2) {
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        xyz[i] = v1.xyz[i] - v2.xyz[i];
    }
    Vector3 newVector = Vector3(xyz[0],xyz[1],xyz[2]);
    return newVector;
}

// vector scalar multiplication
Vector3 operator * (const float scalar, const Vector3& v1){
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        xyz[i] = v1.xyz[i] * scalar;
    }
    Vector3 newVector = Vector3(xyz[0],xyz[1],xyz[2]);
    return newVector;
}