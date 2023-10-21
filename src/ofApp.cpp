#include "ofApp.hpp"
#include "snake.hpp"
#include "food.hpp"

#define FOODS_COUNT 3

static Snake player;
static std::vector<Food> foods(FOODS_COUNT);
static bool gameOver = false;

void ofApp::setup()
{
    generate(foods.begin(), foods.end(), [](){return Food();});
}

void ofApp::draw()
{
    if(gameOver) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        ofExit();
    }

    // handle game-over states
    if(player.IsDead()) {
        ofClear(0);
        ofDrawBitmapString("Game Over.", GAME_WIDTH / 2, GAME_HEIGHT / 2);
        gameOver = true;
        return;
    }

    for(auto &food: foods) 
    food.Render();
    player.Render();
    player.Grow(player.Eat(foods));
}

/**
 * Keep track of the delta time and move the player
 * in a set stable interval.
 */
static thread_local double tickTimeMs = 0;
static constexpr unsigned short int tickTimeMaxMs = 120;
static double deltaTimeMs = 0;
static double prevGameTimeMs = 0;

void ofApp::update()
{
    double currentGameTime = ofGetElapsedTimeMillis();
    deltaTimeMs = currentGameTime - prevGameTimeMs;
    prevGameTimeMs = currentGameTime;

    tickTimeMs += deltaTimeMs;
    if(tickTimeMs >= tickTimeMaxMs) {
        tickTimeMs = 0;
        player.Move();
    }
}

/**
 * Handle player controls and move the snake
 * with the arrow keys.
 */
void ofApp::keyReleased(int key)
{
    switch(key) 
    {
    case OF_KEY_LEFT:
        player.Move(Snake::Left);
        break;
    case OF_KEY_RIGHT:
        player.Move(Snake::Right);
        break;
    case OF_KEY_UP:
        player.Move(Snake::Up);
        break;
    case OF_KEY_DOWN:
        player.Move(Snake::Down);
        break;
    }
}