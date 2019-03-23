// Brett Layman
// 2/21/2018


#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H


// base class for all matrix types
class Matrix {
protected:
    float* thisMatrix; // stores actual matrix data

public:
    int rows;
    int columns;
    // assign rows and columns
    Matrix(int inRows, int inColumns){
        rows = inRows;
        columns = inColumns;
        thisMatrix = new float[inColumns * inRows];
        for (int i = 0; i < inColumns * inRows; ++i) {
            thisMatrix[i] = 0;
        }
    }
    float* getMatrix() const;
    void createMatrix(float* mat);
    void printMatrix();
};


// scale Matrix
class ScaleMatrix : public Matrix {
private:
    float x; // x axis scalar
    float y; // y axis scalar
    float z; // z axis scalar
public:
    // assign default x and y scaling
    ScaleMatrix(int rows, int columns, float inX, float inY, float inZ) : Matrix(rows, columns){
        x = inX;
        y = inY;
        z = inZ;
        createMatrix(0);
    }
    void createMatrix(float time);
    void setXYZ(float xscale, float yscale, float zscale) {
        x = xscale;
        y = yscale;
        z = zscale;
        createMatrix(0);
    }
};


// translate Matrix
class TranslateMatrix : public Matrix {
private:
    float x; // x shift
    float y; // y shift
    float z; // z shift

public:
    // assign default x and y translation (shift)
    TranslateMatrix(int rows, int columns, float inX, float inY, float inZ) : Matrix(rows, columns){
        x = inX;
        y = inY;
        z = inZ;
        createMatrix(0);
    }
    void createMatrix(float time);
    void setXYZ(float inX, float inY, float inZ){
        x = inX;
        y = inY;
        z = inZ;
        createMatrix(0);
    }
};


// rotate Matrix
class RotateMatrix : public Matrix {
private:
    float x; // x rotation angle
    float y; // y rotation angle
    float z; // z rotation angle
public:
    // set default angle in constructor
    RotateMatrix(int rows, int columns, float inX, float inY, float inZ) : Matrix(rows, columns){
        x = inX;
        y = inY;
        z = inZ;
    }
    void createZMatrix(float time);
    void createXMatrix(float time);
    void createYMatrix(float time);
    void setXYZ(float inX, float inY, float inZ){
        x = inX;
        y = inY;
        z = inZ;
    }
};

// orthagonal projection matrix
class OrthoMatrix : public Matrix {
public:
    OrthoMatrix(int rows, int columns) : Matrix(rows, columns){}

    void createMatrix(float l, float r, float b, float t, float n, float f);
};

// perspective projection matrix
class PerspMatrix : public Matrix {
public:
    PerspMatrix(int rows, int columns) : Matrix(rows, columns){}

    void createMatrix(float width, float ratio, float n, float f);
};

// perspective projection matrix
class LookMatrix : public Matrix {
public:
    LookMatrix(int rows, int columns) : Matrix(rows, columns){}

    void createMatrix();
};


// perspective projection matrix
class IdentityMatrix : public Matrix {
public:
    IdentityMatrix (int rows, int columns) : Matrix(rows, columns){
        createMatrix();
    }

    void createMatrix();
};



#endif //LAB3_MATRIX_H
