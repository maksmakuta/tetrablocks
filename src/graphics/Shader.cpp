#include "Shader.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#include "gl/gl.h"

namespace tetrablocks::graphics {

    namespace details {

        unsigned int compileShader(const unsigned int type, const std::string& source) {
            const unsigned int id = glCreateShader(type);
            const char* src = source.c_str();

            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            int success;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(id, 512, nullptr, infoLog);
                std::cerr << "Shader Compilation Error (" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "):\n"
                          << infoLog << std::endl;
            }

            return id;
        }

        unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader) {
            const unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
            const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

            const unsigned int program = glCreateProgram();
            glAttachShader(program, vs);
            glAttachShader(program, fs);
            glLinkProgram(program);

            int success;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(program, 512, nullptr, infoLog);
                std::cerr << "Shader Linking Error:\n" << infoLog << std::endl;
            }

            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }

        std::string readAll(const std::string& path) {
            std::ifstream file(path);
            if (!file) {
                std::cerr << "Error: could not open shader file: " << path << std::endl;
                return "";
            }

            std::stringstream ss;
            ss << file.rdbuf();
            return ss.str();
        }

    }

    void Shader::fromMem(const std::string& vertexSource, const std::string& fragmentSource){
        m_ID = details::createProgram(vertexSource, fragmentSource);
    }

    void Shader::fromFiles(const std::string& vertexPath, const std::string& fragmentPath){
        fromMem(details::readAll(vertexPath), details::readAll(fragmentPath));
    }

    void Shader::setInt(const std::string& name, const int value) const {
        glUniform1i(glGetUniformLocation(m_ID,name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, const float value) const {
        glUniform1f(glGetUniformLocation(m_ID,name.c_str()), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& vec) const {
        glUniform2fv(glGetUniformLocation(m_ID,name.c_str()), 1, &vec[0]);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& vec) const {
        glUniform3fv(glGetUniformLocation(m_ID,name.c_str()), 1, &vec[0]);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& vec) const {
        glUniform4fv(glGetUniformLocation(m_ID,name.c_str()), 1, &vec[0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_ID,name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::clear() {
        glDeleteProgram(m_ID);
        m_ID = 0;
    }

    unsigned int Shader::handle() const {
        return m_ID;
    }

}
