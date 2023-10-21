#pragma once

#include <vector>
#include "cell.hpp"
#include "food.hpp"

class Snake 
{
public:
    /**
     * Initially the snake spawns at a random position.
     */
    Snake();
public:
    /**
     * The directions in which the snake can go.
     */
    enum Direction { 
        Left, Right, Up, Down, DIRECTION_LAST_VALUE };

    /**
     * Move the snake in it's current direction. 
     */
    void Move();

    /**
     * All in one method to validate/move the snake.
     * @param dir The direction to which we move the snake.
     */
    void Move(Direction dir);

    /**
     * Renders the snake on screen.
     */
    void Render();

    /**
     * Attempt to eat food.
     * Return the amount of food eaten.
     * 
     * @note The snake can only eat one cell of food
     * at a time, but some food cells can be more
     * tummy filling than others.
     */
    unsigned int Eat(std::vector<Food> &foods);

    /**
     * When called, the snake grows by N.
     */
    void Grow(int N);

    /**
     * Get's the direction to which the tail has
     * to extend towards.
     * 
     * @note Tail must have at least two cells.
     */
    Direction GetTailDirection();

    /**
     * @return true if the snake is out of bounds 
     * or eating itself, false otherwise.
     */
    bool IsDead();
private:
    Direction _dir;
    Cell _head;
    std::vector<Cell> _tail;
};