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
    GLuint getUniformLocation(const std::string &uniformName);

private:
    int _numAttributes;

    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    void compileShader(const std::string &filePath, GLuint id);
};

#endif
