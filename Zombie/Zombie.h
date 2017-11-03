#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Agent.h"

class Zombie : public Agent {
public:
    Zombie();
    ~Zombie();

    virtual void update();
};

#endif // ZOMBIE_H
