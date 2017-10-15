#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <string>

class ResourceManager
{
public:
    static GLTexture getTexture(std::string texturePath);
    static GLuint bondTexture;

private:
    static TextureCache _textureCache;

};

#endif
