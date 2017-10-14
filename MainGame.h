#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "Errors.h"
#include "GLTexture.h"

enum class GameState { PLAY, EXIT };

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
    void initDebugCallback();

    SDL_Window *_window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Sprite _sprite;
    GLSLProgram _colorProgram;
    GLTexture _playerTexture;

    float _time;
};

#endif
