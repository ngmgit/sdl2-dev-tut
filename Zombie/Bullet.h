#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <glm/glm.hpp>

#include <Myengine/SpriteBatch.h>

class Human;
class Zombie;

const int BULLET_RADIUS = 5;

class Bullet {
public:
    Bullet(float damage, glm::vec2 position, glm::vec2 direction, float speed);
    ~Bullet();

    void update(std::vector<Human*> &humans,
                std::vector<Zombie*> &zombies);

    void draw(Myengine::SpriteBatch &spriteBatch);
private:
    float _damage;
    glm::vec2 _position;
    glm::vec2 _direction;
    float _speed;
};

#endif
