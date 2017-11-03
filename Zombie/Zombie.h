#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Agent.h"

class Zombie : public Agent {
public:
    Zombie();
    ~Zombie();

    virtual void update(const std::vector<std::string> &levelData,
        std::vector<Human*> &humans,
        std::vector<Zombie*> &zombies);
};

#endif // ZOMBIE_H
