#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace Myengine {

enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

struct Glyph {
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
};

class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
        offset(Offset), numVertices(NumVertices), texture(Texture) {
    }

    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch {
public:
    SpriteBatch();
    ~SpriteBatch();

    void init();
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float  depth, const ColorRGBA8 &color);
    void renderBatch();

private:
    GLuint _vbo;
    GLuint _vao;

    std::vector<Glyph*> _glyphs;
    GlyphSortType _sortType;

    std::vector<RenderBatch> _renderBatches;

    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();

    static bool compareFrontToBack(Glyph *a, Glyph *b);
    static bool compareBackToFront(Glyph *a, Glyph *b);
    static bool compareTexture(Glyph *a, Glyph *b);
};

}
#endif // SPRITEBATCH_H
