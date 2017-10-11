#include <fstream>
#include <vector>

#include "GLSLProgram.h"
#include "Errors.h"

GLSLProgram::GLSLProgram()
    : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
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

    shaderFile.close();

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
        glEnableVertexAttribArray(0);
    }
}
