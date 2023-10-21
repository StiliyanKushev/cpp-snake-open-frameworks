#include <random>
#include "ofMain.h"
#include "rengine.hpp"
#include "ofApp.hpp"
#include "snake.hpp"
#include "food.hpp"

#define HEAD_COLORS 26, 199, 10
#define TAIL_COLORS 120, 181, 114
#define INITIAL_TAIL_LENGTH 2

static thread_local std::uniform_int_distribution dist(
    0, Snake::DIRECTION_LAST_VALUE - 1);

// we'll use that to make sure the player only
// switches the direction once before the next 
// move tick.
static bool changeDirectionLock = false;

Snake::Snake() 
{
    // generate random starting direction
    _dir = (Snake::Direction)dist(engine);

    // spawn the head at random location
    _head = Cell();

    // spawn the body attached to the head
    Grow(INITIAL_TAIL_LENGTH);
}

void Snake::Move() 
{
    // move the body of the tail (except the cell attached
    // to the head) towards the head
    for(int i = _tail.size() - 1; i >= 1; i--) {
        auto &c = _tail.at(i);
        auto &p = _tail.at(i-1);
        c.row = p.row;
        c.col = p.col;
    }

    // move the cell of the tail attached to the head
    // to the position of the head
    auto &attached = _tail.front();
    attached.row = _head.row;
    attached.col = _head.col;

    // move the head
    switch (_dir)
    {
    case Snake::Left:
        _head.col--;
        break;
    case Snake::Right:
        _head.col++;
        break;
    case Snake::Up:
        _head.row--;
        break;
    case Snake::Down:
        _head.row++;
        break;
    default:
        break;
    }

    // teleport head if outside of bounds
    if(_head.col < 0)
        _head.col = GAME_CELLS - 1;
    if(_head.col > GAME_CELLS - 1)
        _head.col = 0;
    if(_head.row < 0)
        _head.row = GAME_CELLS - 1;
    if(_head.row > GAME_CELLS - 1)
        _head.row = 0;

    // enable player moving again
    changeDirectionLock = false;
}

void Snake::Move(Direction dir) 
{
    if(changeDirectionLock) return;

    // disallow opposite direction change
    if(dir == Snake::Right && _dir == Snake::Left) return;
    if(dir == Snake::Left && _dir == Snake::Right) return;
    if(dir == Snake::Up && _dir == Snake::Down) return;
    if(dir == Snake::Down && _dir == Snake::Up) return;

    _dir = dir;

    // disable player moving until next tick
    changeDirectionLock = true;
}

void Snake::Render()
{
    // render the head of the snake
    ofSetColor(HEAD_COLORS);
    _head.Render();

    // render the tail of the snake
    ofSetColor(TAIL_COLORS);
    for(auto cell: _tail) {
        cell.Render();
    }
}

unsigned int Snake::Eat(std::vector<Food> &foods)
{
    for(size_t i = 0; i < foods.size(); i++) {
        auto &f = foods[i];
        if(f.row == _head.row && f.col == _head.col) {
            auto growth = f.growthRate;
            foods.erase(foods.begin() + i);
            foods.push_back(Food());
            return growth;
        }
    }
    return false;
}

Snake::Direction Snake::GetTailDirection() {
    const int _tailSize = _tail.size();
    auto &secondToLastCell = _tail.at(_tailSize - 2);
    auto &lastCell = _tail.back();

    if(secondToLastCell.col < lastCell.col)
        return Snake::Left;
    if(secondToLastCell.col > lastCell.col)
        return Snake::Right;
    if(secondToLastCell.row < lastCell.row)
        return Snake::Up;
    if(secondToLastCell.row > lastCell.row)
        return Snake::Down;
    
    // <unreachable code>
    return Snake::DIRECTION_LAST_VALUE;
}

void Snake::Grow(const unsigned short int N)
{
    // no more growing needed
    if(N==0) return;

    /**
     * @brief Lambda function to extend the tail
     * in a given direction relative to a given target
     * by a given size.
     */
    auto extendInDirection = [this](
        Snake::Direction dir, 
        Cell &target,
        const unsigned short int size) 
    {
        for(int i = 1; i <= size; i++) {
            switch(dir)
            {
            case Snake::Left:
                _tail.push_back(Cell(target.row, target.col-i));
                break;
            case Snake::Right:
                _tail.push_back(Cell(target.row, target.col+i));
                break;
            case Snake::Up:
                _tail.push_back(Cell(target.row-i, target.col));
                break;
            case Snake::Down:
                _tail.push_back(Cell(target.row+i, target.col));
                break;
            default:
                break;
            }
        }
    };

    auto getOppositeDirection = [](Snake::Direction dir)
    {
        switch(dir)
        {
        case Snake::Left:
            return Snake::Right;
        case Snake::Right:
            return Snake::Left;
        case Snake::Up:
            return Snake::Down;
        case Snake::Down:
            return Snake::Up;
        default:
            break;
        }
        // <unreachable code>
        return Snake::DIRECTION_LAST_VALUE;
    };

    // attach the tail (in the opposite direction)
    if(_tail.size() == 0) {
        extendInDirection(getOppositeDirection(_dir), _head, N);
        return;
    }
    
    // extend the tail
    Snake::Direction tailDir = GetTailDirection();
    extendInDirection(getOppositeDirection(tailDir), _tail.back(), N);
}

bool Snake::IsDead() {
    // check if head is inside tail
    for(auto &t: _tail) {
        if(t.row == _head.row && t.col == _head.col)
            return true;
    }

    // snake is still alive
    return false;
}