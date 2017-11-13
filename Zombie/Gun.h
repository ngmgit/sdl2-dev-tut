#ifndef GUN_H
#define GUN_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Bullet.h"

class Gun {
public:
    Gun(std::string name, int fireRate, int bulletsPerShot, float spread , float bulletSpeed, float bulletDamage);
    ~Gun();

    void update(bool isMouseDown, const glm::vec2 &position, const glm::vec2 &direction, std::vector<Bullet> &bullets);

private:
    void fire(const glm::vec2 &position, const glm::vec2 &direction, std::vector<Bullet> &bullets);

    std::string _name;
    int _fireRate; ///< firerate in terms of frames
    int _bulletsPerShot; ///< How many bullets should be shot
    float _spread; ///< Accuracy
    float _bulletSpeed;
    float _bulletDamage;
    int _frameCounter;
};

#endif
