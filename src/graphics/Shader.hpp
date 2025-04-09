#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>

namespace tetrablocks::graphics {

    class Shader {
    public:
        Shader() = default;

        void fromMem(const std::string& vertexSource, const std::string& fragmentSource);
        void fromFiles(const std::string& vertexPath, const std::string& fragmentPath);

        void deinit();
        [[nodiscard]] unsigned int handle() const;

        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& vec) const;
        void setVec3(const std::string& name, const glm::vec3& vec) const;
        void setVec4(const std::string& name, const glm::vec4& vec) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        unsigned int m_ID{0};

    };

}

#endif //SHADER_HPP
