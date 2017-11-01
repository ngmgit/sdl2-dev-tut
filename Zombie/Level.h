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

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Myengine::SpriteBatch _spriteBatch;

    glm::ivec2 _startPlayerPos;
    std::vector<glm::ivec2> _zombieStartPos;

};

#endif // LEVEL_H
