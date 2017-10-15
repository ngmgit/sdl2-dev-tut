#include <fstream>
#include <vector>
#include <iostream>

#include "GLSLProgram.h"
#include "Errors.h"

GLSLProgram::GLSLProgram()
    : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
}

void GLSLProgram::compileShaders(const std::string &vertexShaderPath,
                                 const std::string &fragmentShaderPath)
{
    _programID = glCreateProgram();

    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    if (_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created");
    }

    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if (_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created");
    }

    compileShader(vertexShaderPath, _vertexShaderID);
    compileShader(fragmentShaderPath, _fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
    // Attach our shaders to our program
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    // Link our _programID
    glLinkProgram(_programID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(_programID);
        // Don't leak shaders either.
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link");
    }

    // Always detach shaders after a successful link.
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string &attributeName)
{
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName)
{
    GLint location = glGetUniformLocation(_programID, uniformName.c_str());
    if((unsigned)location == GL_INVALID_INDEX) {
        fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
}

void GLSLProgram::compileShader(const std::string &filePath, GLuint id)
{
    // Read shader file content
    std::fstream shaderFile(filePath);
    if (shaderFile.fail()) {
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(shaderFile, line)) {
        fileContents += line + "\n";
    }

    const char *contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);

    glCompileShader(id);


    // Error checking to understand the shader file errors
    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader compile failed with path " + filePath);
    }
}


void GLSLProgram::use()
{
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unUse()
{
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

void GLSLProgram::openglCallbackFunction(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{

    std::cout << "*** OPENGL DEBUG CALLBACK: START ***" << std::endl;
    std::cout << "message: "<< message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }

    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";

    switch (severity){
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "*** OPENGL DEBUG CALLBACK: END ***" << std::endl;
}
