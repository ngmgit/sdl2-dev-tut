#ifndef PLAYER_H
#define PLAYER_H

#include "Human.h"
#include <Myengine/InputManger.h>

class Player : public Human {
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 pos, Myengine::InputManger* inputManger);
    void update(const std::vector<std::string> &levelData,
        std::vector<Human*> &humans,
        std::vector<Zombie*> &zombies);

private:
    Myengine::InputManger* _inputManager;
};

#endif // PLAYER_H
