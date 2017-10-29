#ifndef BULLET_H
#define BULLET_H

#include <glm/glm.hpp>
#include "Myengine/SpriteBatch.h"

class Bullet {
public:
    Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
    ~Bullet();

    void draw(Myengine::SpriteBatch &spriteBatch);
    // returns true when we are out of lifeTime
    bool update();

private:
    float _speed;
    glm::vec2 _direction;
    glm::vec2 _position;
    int _lifeTime;
};

#endif // BULLET_H
