#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>

#include "Errors.h"

void fatalError(const std::string &errorString)
{
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit ...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
    exit(69);
}
