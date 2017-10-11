#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>

class Sprite {
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height);
    void draw() const;

private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
};

#endif
