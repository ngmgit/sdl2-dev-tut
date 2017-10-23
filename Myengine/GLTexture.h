#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

namespace Myengine {

struct GLTexture {
    GLuint id;
    unsigned long int width;
    unsigned long int height;
};

}

#endif
