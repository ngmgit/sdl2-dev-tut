#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <string>

namespace Myengine {

class ResourceManager
{
public:
    static GLTexture getTexture(std::string texturePath);
    static GLuint boundTexture;

private:
    static TextureCache _textureCache;

};

}

#endif
