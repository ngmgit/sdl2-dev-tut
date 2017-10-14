#include "IOManager.h"
#include <fstream>

static bool IOManager::readFileToBuffer(std::string filePath, std::vector<char> &buffer)
{
    std::ifstream file(filePath, std::ios::binary);

    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }

    // seek to the end of the file
    file.seekg(0, std::ios::end);

    // get file size
    int fileSize = file.tellg();

    file.seekg(0, std::ios::beg);

    // exclude file header info: Not necessary, just to be safe
    fileSize -= fileSize.tellg();

    buffer.resize(fileSize);
    file.read(&(buffer[0]), fileSize);
}
