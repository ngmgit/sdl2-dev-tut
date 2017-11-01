#ifndef MAINGAME_H
#define MAINGAME_H

#include <vector>

#include "Myengine/Window.h"
#include "Myengine/GLSLProgram.h"
#include "Myengine/Camera2D.h"
#include "Myengine/InputManger.h"

#include "Zombie/Level.h"

enum class GameState {
    PLAY,
    EXIT
};
class MainGame {
public:
    MainGame();
    ~MainGame();

    // runs the game
    void run();

private:
    // initiaize the core system
    void initSystems();
    // initialize the shaders
    void initShaders();

    // Handle the input processing
    void processInput();
    // Main game loop for the program
    void gameLoop();
    // Render the game
    void drawGame();

    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _fps;

    Myengine::Window      _window;
    Myengine::GLSLProgram _textureProgram;
    Myengine::Camera2D    _camera;
    Myengine::InputManger _inputManger;

    std::vector<Level*> _levels;
};

#endif
