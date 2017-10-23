#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace Myengine {

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
    // use auto to avoid the type declaration std::map<std::string, GLTexture>::iterator
    auto mit = _textureMap.find(texturePath);

    if (mit == _textureMap.end()) {
        // Load the texture;s
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        // Insert it into the map
        _textureMap.insert(make_pair(texturePath, newTexture));

        std::cout << "Info: Loaded Texture! \n";

        return newTexture;
    }

    std::cout << "Info: Loaded Cached Texture! \n";
    return mit->second;
}

}
