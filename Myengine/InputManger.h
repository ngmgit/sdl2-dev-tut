#ifndef INPUTMANGER_H
#define INPUTMANGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Myengine {

class InputManger {
public:
    InputManger();
    ~InputManger();

    void update();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    void setMouseCoords(float x, float y);
    // returns true if the key is held down
    bool isKeyDown(unsigned int keyID);
    // returns true if the key is just pressed
    bool isKeyPressed(unsigned int keyID);

    glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
    bool wasKeyDown(unsigned int keyID);

    std::unordered_map<unsigned int, bool> _keyMap;
    std::unordered_map<unsigned int, bool> _previousKeyMap;
    glm::vec2 _mouseCoords;

};

}
#endif // INPUTMANGER_H
