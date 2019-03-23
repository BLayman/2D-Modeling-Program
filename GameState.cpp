// Brett Layman
// 2/20/2018

#include "GameState.h"

// initialization of static GameState object variables

float GameState::orthoWidth = 64;
float GameState::orthoHeight = 48;

// variables for storing camera position
float GameState::vx = 0;
float GameState::vy = 0;
float GameState::vz = 20;

float GameState::vxPrev;
float GameState::vyPrev;

// scale
float GameState::sx = 1;
float GameState::sy = 1;
float GameState::sz = 1;

// rotate
float GameState::rx = 0;
float GameState::ry = 0;
float GameState::rz = 0;

// translate
float GameState::tx = 0;
float GameState::ty = 0;
float GameState::tz = 0;


// shape creation flags
bool GameState::createSquare = false;
bool GameState::createCircle = false;
bool GameState::createTriangle = false;
bool GameState::createCustom = false;

// selection flags
bool GameState::selected = false;
bool GameState::foundSelected = false;


bool GameState::changedMode = false;
Mode GameState::mode = stamp ;
SetColor GameState::setColor = dont;

// mouse selection flags
double GameState::startDragX = 0;
double GameState::startDragY = 0;
double GameState::finishDragX = 0;
double GameState::finishDragY = 0;
bool GameState::mouseDragged = false;

bool GameState::persp = false;








