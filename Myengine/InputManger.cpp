#include "InputManger.h"


namespace Myengine {

InputManger::InputManger() : _mouseCoords(0.0f)
{
}

InputManger::~InputManger()
{
}

void InputManger::update()
{
    // loop through _keyMap using a for each loop, copy it over to _previousKeyMap
    for (auto& it : _keyMap ) {
        _previousKeyMap[it.first] = it.second;
    }
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

bool InputManger::isKeyDown(unsigned int keyID)
{
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

bool InputManger::isKeyPressed(unsigned int keyID)
{
    // check if it was pressed this frame and wasnt presed the prev frame
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
        return true;
    }
    return false;
}

bool InputManger::wasKeyDown(unsigned int keyID)
{
    auto it = _previousKeyMap.find(keyID);
    if (it != _previousKeyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

}
