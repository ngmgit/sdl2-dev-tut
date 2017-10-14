#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "GLTexture.h"
#include <string>

class ImageLoader {
public:
    GLTexture loadPNG(std::string filePath);
};

#endif
