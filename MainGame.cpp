#include "MainGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <Myengine/Myengine.h>
#include <Myengine/Timer.h>

MainGame::MainGame() :
    _screenWidth(1024),
    _screenHeight(768),
    _gameState(GameState::PLAY)

{
}

MainGame::~MainGame()
{
    for (int i = 0; i < _levels.size(); i++) {
        delete _levels[i];
    }
}

void MainGame::run()
{
    initSystems();

    gameLoop();
}

void MainGame::initSystems()
{
    Myengine::init();
    _window.createWindow("Zombie Game", _screenWidth, _screenHeight, 0);

    initShaders();

    _levels.push_back(new Level("levels/level1.txt"));
}

void MainGame::initShaders()
{
    _textureProgram.compileShaders("shaders/colorShading.vert",
                                 "shaders/colorShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
    Myengine::FpsLimiter fpsLimiter;
    fpsLimiter.setMaxFps(60.0f);

    while (_gameState == GameState::PLAY) {
        fpsLimiter.begin();

        processInput();
        drawGame();

        _fps = fpsLimiter.end();
    }
}

void MainGame::processInput()
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                break;
            case SDL_MOUSEMOTION:
                _inputManger.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManger.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManger.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManger.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManger.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _window.swapBuffer();
}
