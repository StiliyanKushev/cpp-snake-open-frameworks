#pragma once

#include "ofMain.h"

/**
 * This object represents a cell living
 * in a cell-like grid/world and abstracts
 * coordinates in the form of rows and columns. 
 */
class Cell {
public:
    /**
     * Create an cell with random row and
     * column by default.
     */
    Cell();

    /**
     * Create an cell with a set row and
     * column instead of randomly generating it.
     */
    Cell(int row, int col);

    /**
     * Renders the cell on screen.
     * 
     * @note 
     * Color filling should be set prior 
     * to calling this function.
     */
    virtual void Render();

    /**
     * The row and column of the cell.
     */
    int row;
    int col;
private:
    /**
     * Converts a given cell location to
     * it's respective viewport coordinates
     * inside the window.
     * 
     * @param row 
     * @param col 
     * @return ofPoint 
     */
    static ofPoint PointFromCell(int row, int col);
};