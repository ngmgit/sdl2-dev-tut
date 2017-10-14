#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <vector>

class IOManger {
public:
    static bool readFileToBuffer(std::string filePath, std::vector<char> &buffer);
};

#endif
