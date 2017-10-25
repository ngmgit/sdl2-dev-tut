#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "Myengine/GLSLProgram.h"
#include "Myengine/Errors.h"
#include "Myengine/Window.h"
#include "Myengine/Camera2D.h"
#include "Myengine/SpriteBatch.h"

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
    void calculateFPS();

    Myengine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Myengine::GLSLProgram _colorProgram;
    Myengine::Camera2D _camera;
    Myengine::SpriteBatch _spriteBatch;

    float _time;
    float _fps;
    float _frameTime;
    float _maxFPS;
};

#endif
