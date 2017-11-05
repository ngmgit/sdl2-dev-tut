#include "MainGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <Myengine/Myengine.h>
#include <Myengine/Timer.h>
#include "Zombie/Zombie.h"

MainGame::MainGame() :
    _screenWidth(1024),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _player(nullptr)
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
    initLevel();
    gameLoop();
}

void MainGame::initSystems()
{
    Myengine::init();
    _window.createWindow("Zombie Game", _screenWidth, _screenHeight, 0);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    initShaders();

    _agentSpriteBatch.init();

    _camera.init(_screenWidth, _screenHeight);
}

void MainGame::initLevel()
{
    _levels.push_back(new Level("levels/level1.txt"));
    _currentLevel = 0;

    _player = new Player();
    _player->init(5.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManger);

    _humans.push_back(_player);
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

        updateAgents();

        _camera.setPosition(_player->getPosition());
        _camera.update();

        drawGame();

        _fps = fpsLimiter.end();
    }
}

void MainGame::updateAgents()
{
    // update all humans
    for (int i = 0; i <_humans.size(); i++) {
        _humans[i]->update(_levels[_currentLevel]->getLevelData(),
                           _humans,
                           _zombies);
    }

    //Dont forget to update zombies
}

void MainGame::processInput()
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
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
    // set base depth here
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _textureProgram.use();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);

    // Make sure the texture uses texture 0
    GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab and set the camera Matrix
    glm::mat4 projectionMatrix = _camera.getCameraMatrix();
    GLint pUniform = _textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // draw the level
    _levels[_currentLevel]->draw();

    // SpriteBatch Begin - Agent
    _agentSpriteBatch.begin();
    // Draw the humans
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->draw(_agentSpriteBatch);
    }
    _agentSpriteBatch.end();
    _agentSpriteBatch.renderBatch();

    _textureProgram.unUse();

    _window.swapBuffer();
}
