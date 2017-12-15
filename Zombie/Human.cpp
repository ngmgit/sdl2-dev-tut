#include "Human.h"
#include <ctime>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

Human::Human() :
    _frames(0)
{
}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
    _health = 20;

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _color.r = 200;
    _color.g = 0;
    _color.b = 200;
    _color.a = 255;

    _speed = speed;
    _position = pos;
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));

    if (_direction.length() == 0) {
        _direction = glm::vec2(1.0f, 0.0f);
    }

    _direction = glm::normalize(_direction);
}

void Human::update(const std::vector<std::string> &levelData,
    std::vector<Human*> &humans,
    std::vector<Zombie*> &zombies,
    float deltaTime)
{
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-40.0f * 3.14159265359f / 180, 40.0f * 3.14159265359f / 180);

    _position += _direction * _speed * deltaTime;

    if(_frames == 25) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    } else {
        _frames++;
    }


    if (collideWithLevel(levelData)) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    }
}
