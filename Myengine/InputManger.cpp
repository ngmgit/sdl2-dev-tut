#include "InputManger.h"


namespace Myengine {

InputManger::InputManger()
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
