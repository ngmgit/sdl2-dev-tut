#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace Myengine {

enum WindowFlags { INVISIBLE = 0x1 , FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window
{
public:
    Window();
    ~Window();

    int createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
    int getScreenWidth() { return _screenWidth; }
    int getScreenHeight() { return _screenHeight; }
    void initDebugCallback();
    void swapBuffer();

private:
    SDL_Window* _sdlWindow;
    int _screenWidth;
    int _screenHeight;

};

}

#endif // WINDOW_H
