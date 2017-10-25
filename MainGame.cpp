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
        // User for frame time measuring
        float startTicks = SDL_GetTicks();

        processInput();
        _time += 0.01;

        _camera.update();

        drawGame();
        calculateFPS();

        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }

        float frameTicks = SDL_GetTicks() - startTicks;
        // Limit fps to max FPS
        if (1000.0f / _maxFPS > frameTicks) {
           SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }

    }
}

void MainGame::processInput()
{
    SDL_Event evnt;

    const float CAMERA_SPEED = 20.0f;
    const float SCALE_SPEED = 0.1f;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT: _gameState = GameState::EXIT; break;
            case SDL_MOUSEMOTION:
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
            case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym) {
                    case SDLK_w:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
                        break;
                    case SDLK_s:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
                        break;
                    case SDLK_a:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
                        break;
                    case SDLK_d:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
                        break;
                    case SDLK_q:
                        _camera.setScale(_camera.getScale() + SCALE_SPEED);
                        break;
                    case SDLK_e:
                        _camera.setScale(_camera.getScale() - SCALE_SPEED);
                        break;
                    case SDLK_ESCAPE:
                        _gameState = GameState::EXIT; break;
                        break;
                }
        }
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

    // set time uniform variable
    GLint timelocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timelocation, _time);

    // set the camera matrix
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    // sprite batch setup
    _spriteBatch.begin();

    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static Myengine::GLTexture texture = Myengine::ResourceManager::getTexture("textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");
    Myengine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    for (int i = 0; i < 1000; i++) {
        _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
        _spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
    }

    _spriteBatch.end();

    _spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);

    _colorProgram.unUse();

    _window.swapBuffer();
}

void MainGame::calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();

    float currentTicks;
    currentTicks = SDL_GetTicks();

    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    prevTicks = currentTicks;

    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count ; i++) {
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    }
    else {
        _fps = 60.0f;
    }
}
