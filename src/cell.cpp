#include <random>
#include "ofMain.h"
#include "rengine.hpp"
#include "ofApp.hpp"
#include "cell.hpp"

static thread_local std::uniform_int_distribution dist(
    1, GAME_CELLS - 1);

Cell::Cell() 
{
    row = dist(engine);
    col = dist(engine);
}

Cell::Cell(int row, int col): row(row), col(col) 
{
}

ofPoint Cell::PointFromCell(int row, int col) 
{
    ofPoint point;
    point.x = col * GAME_CELL_SIZE;
    point.y = row * GAME_CELL_SIZE;
    return point;
}

void Cell::Render() 
{
    auto point = Cell::PointFromCell(row, col);
    ofRectangle rect(
        point,
        GAME_CELL_SIZE, 
        GAME_CELL_SIZE);
    ofDrawRectangle(rect);
}