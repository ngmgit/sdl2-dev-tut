#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

Sprite::Sprite() : _x(0.0f), _y(0.0f), _width(0.0f), _height(0.0f), _vboID(0) {}

Sprite::~Sprite()
{
    if (_vboID == 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height, std::string texturePath)
{
    _x      = x;
    _y      = y;
    _width  = width;
    _height = height;

    _texture = ResourceManager::getTexture(texturePath);

    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }

    Vertex vertexData[6];

    // First triangle vertices
    vertexData[0].setVertex(x + width, y + height);
    vertexData[0].setUV(1.0f, 1.0f);

    vertexData[1].setVertex(x, y + height);
    vertexData[1].setUV(0.0f, 1.0f);

    vertexData[2].setVertex(x, y);
    vertexData[2].setUV(0.0f, 0.0f);

    // second triangle vertices
    vertexData[3].setVertex(x, y);
    vertexData[3].setUV(0.0f, 0.0f);

    vertexData[4].setVertex(x + width, y);
    vertexData[4].setUV(1.0f, 0.0f);

    vertexData[5].setVertex(x + width, y + height);
    vertexData[5].setUV(1.0f, 1.0f);

    for (int i = 0; i < 6; i++ ) {
        vertexData[i].setColor(255, 0, 255, 255);
    }
    vertexData[1].setColor(0, 0, 255, 255);
    vertexData[4].setColor(0, 255, 0, 255);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() const
{
    glBindTexture(GL_TEXTURE_2D, _texture.id);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // This is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    // This is the color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // This is the UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
