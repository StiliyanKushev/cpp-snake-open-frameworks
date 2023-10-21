#pragma once

#include "cell.hpp"

class Food: public Cell {
public:
    /**
     * When food is spawned there's a small chance
     * it spawns as a more filling food (special)
     * which when eater grows the player more
     * than usual.
     */
    Food();

    /**
     * How much will a snake grow if it eat's 
     * this food.
     * 
     * By default this is 1, but upon creation
     * there's a chance it can vary.
     */
    int growthRate = 1;

    /**
     * Food is just a cell and as such can be
     * rendered on the screen. We want to be
     * able to render it differently.
     */
    void Render() override;
};