#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include <Myengine/SpriteBatch.h>

const int TILE_WIDTH = 64;
class Level {
public:
    //load the level
    Level(const std::string &fileName);
    ~Level();

    void draw();

    // getters
    const std::vector<std::string>& getLevelData() const { return _levelData; }
    glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
    const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPositions; }

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Myengine::SpriteBatch _spriteBatch;

    glm::vec2 _startPlayerPos;
    std::vector<glm::vec2> _zombieStartPositions;

};

#endif // LEVEL_H
