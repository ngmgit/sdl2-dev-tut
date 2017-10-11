#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "Errors.h"

enum class GameState {PLAY, EXIT};

class MainGame {
public:
    MainGame();
    ~MainGame();

    void run();
    
private:
    void initSystems();
    void initShaders();
    void processInput();
    void gameLoop();
    void drawGame();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Sprite _sprite;
    GLSLProgram _colorProgram;
};