#ifndef INPUTMANGER_H
#define INPUTMANGER_H

#include <unordered_map>

namespace Myengine {

class InputManger {
public:
    InputManger();
    ~InputManger();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    bool isKeyPressed(unsigned int keyID);

private:
    std::unordered_map<unsigned int, bool> _keyMap;
};

}
#endif // INPUTMANGER_H
