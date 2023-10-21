#include "ofMain.h"
#include "ofApp.hpp"

int main()
{
    ofGLWindowSettings settings;
    settings.setSize(GAME_WIDTH, GAME_HEIGHT);
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    ofRunApp(window, make_shared<ofApp>());
    ofRunMainLoop();
}