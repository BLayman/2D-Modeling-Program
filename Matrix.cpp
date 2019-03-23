// Brett Layman
// 2/12/2018
#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "vector3.h"
#include "overloading.h"
#include "GameState.h"
using namespace std;

// get matrix data, must be const method to be used in operator overloading
float* Matrix::getMatrix() const {return thisMatrix;}

// assign input matrix to class matrix data thisMatrix
void Matrix::createMatrix(float* matrix){
    int length = rows * columns;
    copy(matrix,matrix + length,thisMatrix);
}

// print matrix
void Matrix::printMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << thisMatrix[(i * columns) + j] << " " ;
        }
        cout << endl;
    }
}

// use time and class fields to create scale matrix
void ScaleMatrix::createMatrix(float time) {
    float scalefactor = (float) sin(time) + 1;
    float scaleMatrix[] = {
            scalefactor * x,0.0f,0.0f,0.0f,
            0.0f,scalefactor * y,0.0f,0.0f,
            0.0f,0.0f,scalefactor * z,0.0f,
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(scaleMatrix)/sizeof(float);
    copy(scaleMatrix,scaleMatrix + length,thisMatrix);
}


// use time and class fields to create z axis rotation matrix
void RotateMatrix::createZMatrix(float time) {
    float degreeAngle = (float) sin(time) * 360;
    float radianAngle = (degreeAngle * M_PI) / 180;
    float baseAngle = (z * M_PI) / 180;
    float rotateMatrix[] = {
            (float) cos(radianAngle + baseAngle),(float) -sin(radianAngle + baseAngle),0.0f,0.0f,
            (float) sin(radianAngle + baseAngle),(float) cos(radianAngle + baseAngle),0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(rotateMatrix)/sizeof(float);
    copy(rotateMatrix,rotateMatrix + length,thisMatrix);
}

// x axis rotation matrix
void RotateMatrix::createXMatrix(float time) {
    float degreeAngle = (float) sin(time) * 360;
    float radianAngle = (degreeAngle * M_PI) / 180;
    float baseAngle = (x * M_PI) / 180;
    float rotateMatrix[] = {
            1.0f,0.0f,0.0f,0.0f,
            0.0f,(float) cos(radianAngle + baseAngle),(float) -sin(radianAngle + baseAngle),0.0f,
            0.0f,(float) sin(radianAngle + baseAngle),(float) cos(radianAngle + baseAngle),0.0f,
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(rotateMatrix)/sizeof(float);
    copy(rotateMatrix,rotateMatrix + length,thisMatrix);
}

//y axis rotation matrix
void RotateMatrix::createYMatrix(float time) {
    float degreeAngle = (float) sin(time) * 360;
    float radianAngle = (degreeAngle * M_PI) / 180;
    float baseAngle = (y * M_PI) / 180;
    float rotateMatrix[] = {
            (float) cos(radianAngle + baseAngle),0.0f,(float) sin(radianAngle + baseAngle),0.0f,
            0.0f,1.0f,0.0f,0.0f,
            (float) -sin(radianAngle + baseAngle),0.0f,(float) cos(radianAngle + baseAngle),0.0f,
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(rotateMatrix)/sizeof(float);
    copy(rotateMatrix,rotateMatrix + length,thisMatrix);
}


// use time and class fields to create translation matrix
void TranslateMatrix::createMatrix(float time) {
    float translation = sin(time)/ 2;

    float translateMatrix[] = {
            1.0f,0.0f,0.0f,translation + x,
            0.0f,1.0f,0.0f,translation + y,
            0.0f,0.0f,1.0f,translation + z,
            0.0f,0.0f,0.0f,1.0f
    };
    //cout << "z coor: " << translateMatrix[11] << endl;
    int length = sizeof(translateMatrix)/sizeof(float);
    copy(translateMatrix,translateMatrix + length,thisMatrix);
}

// create orthagonal projection matrix
void OrthoMatrix::createMatrix(float l, float r, float b, float t, float n, float f) {
    float orthoMatrix[] = {
            2.0f/(r-l),0.0f,0.0f,-1.0f*((r+l)/(r-l)),
            0.0f,2.0f/(t-b),0.0f,-1.0f*((t+b)/(t-b)),
            0.0f,0.0f,-2.0f/(f-n),-1.0f*((f+n)/(f-n)),
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(orthoMatrix)/sizeof(float);
    copy(orthoMatrix,orthoMatrix + length,thisMatrix);
}

// create perspective projection matrix
void PerspMatrix::createMatrix(float width, float ratio, float n, float f) {
    float l = -width/2;
    float r = width/2;
    float b = -(width*ratio)/2;
    float t = (width*ratio)/2;
    float perspMatrix[] = {
            (2.0f*n)/(r-l),0.0f,(r+l)/(r-l),0.0f,
            0.0f,(2.0f*n)/(t-b),(t+b)/(t-b),0.0f,
            0.0f,0.0f,(-1 *(f+n))/(f-n),(-2.0f*f*n)/(f-n),
            0.0f,0.0f,-1.0f,0.0f
    };
    int length = sizeof(perspMatrix)/sizeof(float);
    copy(perspMatrix,perspMatrix + length,thisMatrix);

}

// camera view direction basis
void LookMatrix::createMatrix() {
    // calculations for creating view matrix
    Vector3 origin = Vector3 (0,0,0);
    Vector3 camLoc = Vector3(GameState::vx, GameState::vy, GameState::vz);
    Vector3 direction = origin - camLoc;
    Vector3 dirNorm = -1 * direction.normalize();
    //dirNorm.print();
    Vector3 worldUp = Vector3(0,1,0);
    Vector3 right = worldUp.cross(dirNorm);
    Vector3 rightNorm = right.normalize();
    //rightNorm.print();
    Vector3 upNorm = dirNorm.cross(rightNorm);
    //Vector3 upNorm = up.normalize();
    // set camera angle
    Matrix lookMatrix = Matrix(4,4);
    float lookData[] = {
            rightNorm.xyz[0], rightNorm.xyz[1], rightNorm.xyz[2],0.0f,
            upNorm.xyz[0], upNorm.xyz[1], upNorm.xyz[2],0.0f,
            dirNorm.xyz[0], dirNorm.xyz[1], dirNorm.xyz[2],0.0f,
            0.0f,0.0f,0.0f,1.0f
    };
    int length = sizeof(lookData)/sizeof(float);
    copy(lookData,lookData + length,thisMatrix);
}

// Identity matrix
void IdentityMatrix::createMatrix() {
    float identity[] = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
    };
    int length = sizeof(identity)/sizeof(float);
    copy(identity,identity + length,thisMatrix);
}

