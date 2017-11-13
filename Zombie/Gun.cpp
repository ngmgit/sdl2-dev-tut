#include "Gun.h"
#include <random>
#include <ctime>

#include <glm/gtx/rotate_vector.hpp>

Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDamage) :
    _name(name),
    _fireRate(fireRate),
    _bulletsPerShot(bulletsPerShot),
    _spread(spread),
    _bulletSpeed(bulletSpeed),
    _bulletDamage(bulletDamage),
    _frameCounter(0)
{
}

Gun::~Gun()
{
}

void Gun::update(bool isMouseDown, const glm::vec2 &position, const glm::vec2 &direction, std::vector<Bullet> &bullets)
{
    _frameCounter++;
    if (_frameCounter >= _fireRate && isMouseDown) {
        fire(position, direction, bullets);
        _frameCounter = 0;
    }
}

void Gun::fire(const glm::vec2 &position, const glm::vec2 &direction, std::vector<Bullet> &bullets)
{
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-_spread * 3.14159265359f / 180, _spread * 3.14159265359f / 180);

    for (int i = 0; i< _bulletsPerShot; i++) {
        bullets.emplace_back(_bulletDamage,
                             position,
                             glm::rotate(direction, randRotate(randomEngine)),
                             _bulletSpeed);
    }

}

