#ifndef TIMER_H
#define TIMER_H

namespace Myengine {

class FpsLimiter {
public:
    FpsLimiter();

    void init(float maxFPS);
    void setMaxFps(float maxFPS);
    void begin();
    // end will return the currrent fps
    float end();

private:
    float _maxFPS;
    unsigned int _startTicks;
    float _fps;
    float _frameTime;

    void calculateFPS();
};

}

#endif // TIMER_H
