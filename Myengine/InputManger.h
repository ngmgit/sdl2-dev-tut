#ifndef INPUTMANGER_H
#define INPUTMANGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Myengine {

class InputManger {
public:
    InputManger();
    ~InputManger();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    void setMouseCoords(float x, float y);
    bool isKeyPressed(unsigned int keyID);

    glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
    std::unordered_map<unsigned int, bool> _keyMap;
    glm::vec2 _mouseCoords;
};

}
#endif // INPUTMANGER_H
