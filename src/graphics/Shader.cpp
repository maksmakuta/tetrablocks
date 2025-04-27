#include "tetrablocks/graphics/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/gl.h"

namespace tetrablocks {

    Shader::Shader() = default;

    GLuint compileShader(const int type, const std::string& source) {
        const GLuint shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            return 0;
        }

        return shader;
    }

    std::string loadFile(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        loadFromFiles(vertexPath, fragmentPath);
    }

    Shader::~Shader() {
        if (m_id) glDeleteProgram(m_id);
    }

    bool Shader::loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
        const std::string vertSource = loadFile(vertexPath);
        const std::string fragSource = loadFile(fragmentPath);

        const uint vertexShader = compileShader(GL_VERTEX_SHADER, vertSource);
        const uint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragSource);

        if (!vertexShader || !fragmentShader) return false;

        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);
        glLinkProgram(m_id);

        int success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return true;
    }

    void Shader::use() const {
        glUseProgram(m_id);
    }

    void Shader::setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    glm::uint Shader::id() const {
        return m_id;
    }

}
