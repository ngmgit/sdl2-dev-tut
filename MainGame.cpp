#include <iostream>
#include <GL/glew.h>

#include "MainGame.h"
#include "Myengine/Myengine.h"
#include "Myengine/ImageLoader.h"
#include "Myengine/ResourceManager.h"
#include "Myengine/GLTexture.h"

MainGame::MainGame()
    : _screenWidth(1024),
      _screenHeight(768),
      _gameState(GameState::PLAY),
      _time(0),
      _maxFPS(60.0f)
{
    _camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
    initSystems();

    gameLoop();
}

void MainGame::initSystems()
{
    Myengine::init();

    _window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);

    initShaders();

    _spriteBatch.init();

    _fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("shaders/colorShading.vert",
                                 "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
    while (_gameState != GameState::EXIT) {

        _fpsLimiter.begin();

        processInput();
        _time += 0.01;

        _camera.update();

        for (int i = 0; i < _bullets.size();) {
            if(_bullets[i].update() == true) {
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
            } else {
                i++;
            }
        }

        drawGame();

        _fps = _fpsLimiter.end();

        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10000) {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}

void MainGame::processInput()
{
    SDL_Event evnt;

    const float CAMERA_SPEED = 3.0f;
    const float SCALE_SPEED = 0.1f;

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

    if (_inputManger.isKeyPressed(SDLK_w)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
    }

    if (_inputManger.isKeyPressed(SDLK_s)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
    }

    if (_inputManger.isKeyPressed(SDLK_a)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
    }

    if (_inputManger.isKeyPressed(SDLK_d)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
    }

    if (_inputManger.isKeyPressed(SDLK_q)) {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }

    if (_inputManger.isKeyPressed(SDLK_e)) {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }

    if (_inputManger.isKeyPressed(SDLK_ESCAPE)) {
        _gameState = GameState::EXIT;
    }

    if (_inputManger.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseCoords = _inputManger.getMouseCoords();
        mouseCoords = _camera.convertScreenToWorld(mouseCoords);

        glm::vec2 playerPosition(0.0f);
        glm::vec2 direction = mouseCoords - playerPosition;
        direction = glm::normalize(direction);

        _bullets.emplace_back(playerPosition, direction, 5.01f, 1000);
    }

}

void MainGame::drawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    // set texture along with its uniform variable
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    // here second param '0' is the texture id, 0 as seen above
    glUniform1i(textureLocation, 0);

    // set the camera matrix
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    // set color, tecture, uv and its position
    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static Myengine::GLTexture texture = Myengine::ResourceManager::getTexture("textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");
    Myengine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    // sprite batch setup
    _spriteBatch.begin();

    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

    for (int i = 0; i < _bullets.size(); i++) {
        _bullets[i].draw(_spriteBatch);
    }

    _spriteBatch.end();

    _spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);

    _colorProgram.unUse();

    _window.swapBuffer();
}
