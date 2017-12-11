#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include <string>

#include <Myengine/SpriteBatch.h>

const float AGENT_WIDTH = 44.0f;

class Zombie;
class Human;

class Agent {
public:
    Agent();
    virtual ~Agent();

    virtual void update(const std::vector<std::string> &levelData,
                        std::vector<Human*> &humans,
                        std::vector<Zombie*> &zombies) = 0;

    bool collideWithLevel(const std::vector<std::string> &levelData);

    bool collideWithAgent(Agent* agent);

    void draw(Myengine::SpriteBatch &spriteBatch);

    // return true if died
    bool applyDamage(float damage);

    glm::vec2 getPosition() const { return _position; }

protected:
    void checkTilePosition(const std::vector<std::string> &levelData,
                           std::vector<glm::vec2> &collideTilePositions,
                           float x, float y);

    void collideWithTile(glm::vec2 tilePos);

    glm::vec2 _position;
    float _speed;
    Myengine::ColorRGBA8 _color;
    float _health;
};

#endif // AGENT_H
