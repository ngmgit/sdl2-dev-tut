#include "MainGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <random>

#include <Myengine/Myengine.h>
#include <Myengine/Timer.h>
#include "Zombie/Zombie.h"
#include <Myengine/Errors.h>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;

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
    _player->init(3.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManger);

    _humans.push_back(_player);

    static std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    static std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    static std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    // Add all the random humans
    for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
        _humans.push_back(new Human);

        glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
        _humans.back()->init(HUMAN_SPEED, pos);
    }

    // Add zombies
    const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
    for (int i = 0; i < zombiePositions.size(); i++) {
        _zombies.push_back(new Zombie);
        _zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
    }
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
    for (int i = 0; i <_zombies.size(); i++) {
        _zombies[i]->update(_levels[_currentLevel]->getLevelData(),
                           _humans,
                           _zombies);
    }

    // update zombie collisions
    for (int i= 0; i < _zombies.size(); i++) {
        // collide with other zombies
        for (int j = i+1; j < _zombies.size(); j++) {
            _zombies[i]->collideWithAgent(_zombies[j]);
        }

        // collide with other humans
        for (int j = 1; j < _humans.size(); j++) {
            if (_zombies[i]->collideWithAgent(_humans[j])) {
                // add the new zombie
                _zombies.push_back(new Zombie);
                _zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
                // and delete the human
                delete _humans[j];
                _humans[j] = _humans.back();
                _humans.pop_back();
            }
        }

        // Collide with Player
        if (_zombies[i]->collideWithAgent(_humans[0])) {
            Myengine::fatalError("You Lose!");
        }
    }

    // update Human collisions
    for (int i= 0; i < _humans.size(); i++) {
        for (int j = i+1; j < _humans.size(); j++) {
            _humans[i]->collideWithAgent(_humans[j]);
        }
    }

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
    // Draw the zombies
    for (int i = 0; i < _zombies.size(); i++) {
        _zombies[i]->draw(_agentSpriteBatch);
    }
    _agentSpriteBatch.end();
    _agentSpriteBatch.renderBatch();

    _textureProgram.unUse();

    _window.swapBuffer();
}
