#ifndef PLAYER_H
#define PLAYER_H

#include "Human.h"
#include <Myengine/InputManger.h>
#include <Myengine/Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human {
public:
    Player();
    ~Player();

    void addGun(Gun* gun);

    void init(float speed, glm::vec2 pos,
              Myengine::InputManger* inputManger,
              Myengine::Camera2D* camera,
              std::vector<Bullet>* bullets);

    void update(const std::vector<std::string> &levelData,
        std::vector<Human*> &humans,
        std::vector<Zombie*> &zombies);

private:
    Myengine::InputManger* _inputManager;
    std::vector<Gun*> _guns;
    int _currentGunIndex;

    Myengine::Camera2D* _camera;
    std::vector<Bullet>* _bullets;
};

#endif // PLAYER_H
