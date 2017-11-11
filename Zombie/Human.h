#ifndef HUMAN_H
#define HUMAN_H

#include "Agent.h"

class Human : public Agent {
public:
    Human();
    virtual ~Human();

    void init(float speed, glm::vec2 pos);

    virtual void update(const std::vector<std::string> &levelData,
        std::vector<Human*> &humans,
        std::vector<Zombie*> &zombies);

private:
    glm::vec2 _direction;
    int _frames;

};

#endif // HUMAN_H
