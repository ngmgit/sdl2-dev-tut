#include "Level.h"

#include <fstream>
#include <iostream>

#include <Myengine/Errors.h>
#include <Myengine/ResourceManager.h>

Level::Level(const std::string &fileName)
{
    std::ifstream file;
    file.open(fileName);

    // Error checking
    if (file.fail()) {
        Myengine::fatalError("Failed to open file " + fileName);
    }

    // throw away the first string in tmp
    std::string tmp;
    file >> tmp >> _numHumans;

    while (std::getline(file, tmp)) {
        _levelData.push_back(tmp);
    }

    _spriteBatch.begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Myengine::Color whiteColor;
    whiteColor.r = 255;
    whiteColor.g = 255;
    whiteColor.b = 255;
    whiteColor.a = 255;

    for (int y = 0; y < _levelData.size(); y++) {
        for ( int x = 0; x < _levelData[y].size(); x++) {
            // Grab the tile
            char tile = _levelData[y][x];

            //get dest rect
            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            switch(tile) {
                case 'B':
                case 'R':
                    _spriteBatch.draw(
                        destRect,
                        uvRect,
                        Myengine::ResourceManager::getTexture("textures/zombie/red_bricks.png").id,
                        0.0f,
                        whiteColor);
                    break;
                case 'G':
                    _spriteBatch.draw(
                        destRect,
                        uvRect,
                        Myengine::ResourceManager::getTexture("textures/zombie/glass.png").id,
                        0.0f,
                        whiteColor);
                    break;
                case 'L':
                    _spriteBatch.draw(
                        destRect,
                        uvRect,
                        Myengine::ResourceManager::getTexture("textures/zombie/light_bricks.png").id,
                        0.0f,
                        whiteColor);
                    break;
                case '@':
                    _startPlayerPos.x = x * TILE_WIDTH;
                    _startPlayerPos.y = y * TILE_WIDTH;
                    break;
                case 'Z':
                    _zombieStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                    break;
                case '.': break;
                default:
                    std::cout  << "Unexpected symbol" << tile << ": " + x << y;
            }
        }
    }

    _spriteBatch.end();

}

Level::~Level()
{
}

void Level::draw()
{
    _spriteBatch.renderBatch();
}
