#include <random>
#include "ofMain.h"
#include "rengine.hpp"
#include "food.hpp"

#define NORMAL_FOOD_COLORS 230, 23, 71
#define SPECIAL_FOOD_COLORS 246, 255, 0

static thread_local std::uniform_int_distribution dist(
    0, 100);

Food::Food() {
    // let's say the food only has a 10%
    // chance of being special.
    auto chance = dist(engine);
    if(chance <= 10) {
        growthRate = 2;
    }
}

void Food::Render() {
    // set the fill color first
    if(growthRate==1) 
        ofSetColor(NORMAL_FOOD_COLORS);
    else 
        ofSetColor(SPECIAL_FOOD_COLORS);

    // render the cell via the method
    // in the base class.
    Cell::Render();
}