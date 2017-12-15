#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include <Myengine/SpriteBatch.h>

class Agent;
class Human;
class Zombie;

const int BULLET_RADIUS = 5;

class Bullet {
public:
    Bullet(float damage, glm::vec2 position, glm::vec2 direction, float speed);
    ~Bullet();

    // when it returns true want to delete the bullet
    bool update(const std::vector<std::string> &levelData, float deltaTime);

    void draw(Myengine::SpriteBatch &spriteBatch);

    bool collideWithAgent(Agent* agent);

    float getDamage() { return _damage; }

private:

    bool collideWithWorld(const std::vector<std::string>&level);
    float _damage;
    glm::vec2 _position;
    glm::vec2 _direction;
    float _speed;
};

#endif
