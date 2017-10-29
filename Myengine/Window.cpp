#include <iostream>

#include "Window.h"
#include "Errors.h"
#include "GLSLProgram.h"

namespace Myengine {

Window::Window()
{
}

Window::~Window()
{
}

int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    Uint32 flags = SDL_WINDOW_OPENGL;

    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }

    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }

    _sdlWindow = SDL_CreateWindow(windowName.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            screenWidth,
                            screenHeight,
                            flags);

    if (_sdlWindow == nullptr) {
        fatalError("SDL window could not be created");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize GLEW!");
    }

    // Print OpenGL version
    std::printf("***    OpenGL Version: %s  ***\n", glGetString(GL_VERSION));

    // initialze asynchronus opengl callback
    initDebugCallback();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Set Vsync
    SDL_GL_SetSwapInterval(0);

    // enable alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void Window::initDebugCallback() {
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

void Window::swapBuffer() {
    SDL_GL_SwapWindow(_sdlWindow);
}

}
