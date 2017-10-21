#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include <Myengine/GLSLProgram.h>
#include <Myengine/Sprite.h>
#include <Myengine/Errors.h>

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

    SDL_Window *_window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::vector<Sprite*> _sprites;
    GLSLProgram _colorProgram;

    float _time;
    float _fps;
    float _frameTime;
    float _maxFPS;
};

#endif
