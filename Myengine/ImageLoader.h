#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "GLTexture.h"
#include <string>

namespace Myengine {

class ImageLoader {
public:
    static GLTexture loadPNG(std::string filePath);
};

}

#endif
