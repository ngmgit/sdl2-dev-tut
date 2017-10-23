#include "Myengine.h"

#include <SDL2/SDL.h>

namespace Myengine {

int init()
{
    // Intiliaize every sdl module
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return 0;
}

}
