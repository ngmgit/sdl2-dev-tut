#ifndef HUMAN_H
#define HUMAN_H

#include "Agent.h"

class Human : public Agent {
public:
    Human();
    virtual ~Human();

    virtual void update();
};

#endif // HUMAN_H
