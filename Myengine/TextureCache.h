#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <string>
#include <map>
#include "GLTexture.h"

namespace Myengine {

class TextureCache {
public:
    TextureCache();
    ~TextureCache();

    GLTexture getTexture(std::string texturePath);

private:
    std::map<std::string, GLTexture> _textureMap;
};

}

#endif
