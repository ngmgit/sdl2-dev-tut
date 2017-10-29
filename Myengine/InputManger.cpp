#include "InputManger.h"


namespace Myengine {

InputManger::InputManger() : _mouseCoords(0.0f)
{
}

InputManger::~InputManger()
{
}

void InputManger::pressKey(unsigned int keyID)
{
    _keyMap[keyID] = true;
}

void InputManger::releaseKey(unsigned int keyID)
{
    _keyMap[keyID] = false;
}

void InputManger::setMouseCoords(float x, float y)
{
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool InputManger::isKeyPressed(unsigned int keyID)
{
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

}
