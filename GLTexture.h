#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

struct GLTexture {
    GLuint id;
    unsigned long int width;
    unsigned long int height;
};

#endif
