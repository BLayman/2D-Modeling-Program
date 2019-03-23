// Brett Layman
// 2/21/2018

#ifndef LAB3_GAMESTATE_H
#define LAB3_GAMESTATE_H

// game modes
enum Mode {view, stamp, group, modify, custom};

// shape colors
enum SetColor {red,green,blue,dont};

// class for holding global data about state of program
class GameState{
public:
    // view window size
    static float orthoWidth;
    static float orthoHeight;

    // variables for storing camera position
    static float vx;
    static float vy;
    static float vz;

    static float vxPrev;
    static float vyPrev;

    // scale
    static float sx;
    static float sy;
    static float sz;

    // rotate
    static float rx;
    static float ry;
    static float rz;

    // translate
    static float tx;
    static float ty;
    static float tz;

    // shape creation
    static bool createTriangle;
    static bool createSquare;
    static bool createCircle;
    static bool createCustom;

    //selection
    static bool selected;
    static bool foundSelected;

    static bool changedMode;
    static Mode mode;
    static SetColor setColor;

    // mouse state
    static double startDragX;
    static double startDragY;
    static double finishDragX;
    static double finishDragY;
    static bool mouseDragged;

    static bool persp;



};


#endif //LAB3_GAMESTATE_H
