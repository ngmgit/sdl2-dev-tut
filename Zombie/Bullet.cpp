#include "Bullet.h"
#include <Myengine/ResourceManager.h>

Bullet::Bullet(float damage, glm::vec2 position, glm::vec2 direction, float speed) :
    _damage(damage),
    _position(position),
    _direction(direction),
    _speed(speed)
{
}

Bullet::~Bullet()
{
}

void Bullet::update(std::vector<Human*> &humans,
                std::vector<Zombie*> &zombies)
{
    _position += _direction * _speed;
}

void Bullet::draw(Myengine::SpriteBatch &spriteBatch)
{
    glm::vec4 destRect(_position.x + BULLET_RADIUS,
                       _position.y + BULLET_RADIUS,
                       BULLET_RADIUS * 2,
                       BULLET_RADIUS * 2);

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    Myengine::Color color;
    color.r = 75;
    color.g = 128;
    color.b = 128;
    color.a = 255;

    spriteBatch.draw(destRect, uvRect, Myengine::ResourceManager::getTexture("textures/zombie/circle.png").id, 0.0f, color);
}
