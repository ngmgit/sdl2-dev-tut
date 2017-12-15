#include "Zombie.h"
#include "Human.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
    _health = 150;
    _speed = speed;
    _position = pos;
    _color = Myengine::ColorRGBA8(0, 160, 0, 255);
}

void Zombie::update(const std::vector<std::string> &levelData,
    std::vector<Human*> &humans,
    std::vector<Zombie*> &zombies,
    float deltaTime)
{
    Human* closestHuman = getNearestHuman(humans);

    if (closestHuman != nullptr) {
        glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
        _position += direction * _speed * deltaTime;
    }

    collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*> &humans)
{
    Human* closestHuman = nullptr;
    float smallestDistance = 999999.0f;

    for (int i = 0; i < humans.size(); i++) {
        glm::vec2 distVec = humans[i]->getPosition() - _position;
        float distance = glm::length(distVec);

        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }

    return closestHuman;
}
