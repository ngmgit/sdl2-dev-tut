#include "Player.h"
#include <SDL2/SDL.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, Myengine::InputManger* inputManger)
{
    _inputManager = inputManger;

    _speed = speed;
    _position = pos;
    _color.r = 0;
    _color.g = 0;
    _color.b = 185;
    _color.a = 255;

}

void Player::update(const std::vector<std::string> &levelData,
    std::vector<Human*> &humans,
    std::vector<Zombie*> &zombies)
{
    if (_inputManager->isKeyPressed(SDLK_w)) {
        _position.y += _speed;
    } else if (_inputManager->isKeyPressed(SDLK_s)) {
        _position.y -= _speed;
    }

    if (_inputManager->isKeyPressed(SDLK_a)) {
        _position.x -= _speed;
    } else if (_inputManager->isKeyPressed(SDLK_d)) {
        _position.x += _speed;
    }

    collideWithLevel(levelData);
}
