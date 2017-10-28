#include "Timer.h"
#include <SDL2/SDL.h>

namespace Myengine {

FpsLimiter::FpsLimiter()
{
}

void FpsLimiter::init(float maxFPS)
{
    setMaxFps(maxFPS);
}

void FpsLimiter::setMaxFps(float maxFPS)
{
    _maxFPS = maxFPS;
}

void FpsLimiter::begin()
{
    _startTicks = SDL_GetTicks();
}

float FpsLimiter::end()
{
    calculateFPS();

    float frameTicks = SDL_GetTicks() - _startTicks;
    // Limit fps to max FPS
    if (1000.0f / _maxFPS > frameTicks) {
        SDL_Delay(1000.0f / _maxFPS - frameTicks);
    }

    return _fps;
}

void FpsLimiter::calculateFPS()
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


}

