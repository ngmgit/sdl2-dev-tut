#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include <Myengine/SpriteBatch.h>

const float AGENT_WIDTH = 60;

class Agent {
public:
    Agent();
    virtual ~Agent();

    virtual void update() = 0;
    void draw(Myengine::SpriteBatch &spriteBatch);
    glm::vec2 getPosition() const { return _position; }

protected:
    glm::vec2 _position;
    float _speed;
    Myengine::Color _color;
};

#endif // AGENT_H
