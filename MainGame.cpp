#include <iostream>

#include "MainGame.h"
#include "ImageLoader.h"

MainGame::MainGame()
    : _window(nullptr),
      _screenWidth(1024),
      _screenHeight(768),
      _gameState(GameState::PLAY),
      _time(0),
      _maxFPS(60.0f)
{
}

MainGame::~MainGame()
{
    SDL_DestroyWindow(_window);
    _window = NULL;
}

void MainGame::run()
{
    initSystems();

    // using sprite pointers
    _sprites.push_back(new Sprite());
    _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");

    for (int i=0; i < 1000; i++) {
        _sprites.push_back(new Sprite());
        _sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");
    }

    // get texture
    //_playerTexture = ImageLoader::loadPNG("textures/jimmy-jump-pack/PNG/CharacterRight_Standing.png");

    gameLoop();
}

void MainGame::initSystems()
{
    // Intiliaize every sdl module
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, _screenWidth,
                               _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL window could not be created");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize GLEW!");
    }

    initDebugCallback();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Disable Vsync
    SDL_GL_SetSwapInterval(0);

    initShaders();
}

void MainGame::initDebugCallback() {
    std::cout << "GL Debug Enabled!" << std::endl;
    glEnable(GL_DEBUG_OUTPUT);

    std::cout << "Register OpenGL debug callback " << std::endl;
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLSLProgram::openglCallbackFunction, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE,
        GL_DONT_CARE,
        GL_DONT_CARE,
        0,
        &unusedIds,
        true);
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

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT: _gameState = GameState::EXIT; break;
            case SDL_MOUSEMOTION:
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}

void MainGame::drawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    // here second param '0' is the texture id, 0 as seen above
    glUniform1i(textureLocation, 0);

    GLint timelocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timelocation, _time);

    for (unsigned int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }

    _colorProgram.unUse();

    SDL_GL_SwapWindow(_window);
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
