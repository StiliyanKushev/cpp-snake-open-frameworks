#pragma once

#include "ofMain.h"

constexpr int GAME_WIDTH = 800;
constexpr int GAME_HEIGHT = 800;
constexpr int GAME_CELLS = 20;
constexpr int GAME_CELL_SIZE = GAME_WIDTH / GAME_CELLS;

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
};