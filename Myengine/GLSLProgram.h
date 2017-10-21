#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram() {}

    void compileShaders(const std::string &vertexShaderPath,
                        const std::string &fragmentShaderPath);
    void linkShaders();
    void addAttribute(const std::string &attributeName);
    void use();
    void unUse();
    GLint getUniformLocation(const std::string &uniformName);

    static void openglCallbackFunction(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);

private:
    int _numAttributes;

    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    void compileShader(const std::string &filePath, GLuint id);
};

#endif
