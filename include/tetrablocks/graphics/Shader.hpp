#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>

namespace tetrablocks {


    class Shader {
    public:
        Shader();
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        bool loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
        void use() const;

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

        [[nodiscard]] glm::uint id() const { return m_id; }

    private:
        glm::uint m_id = 0;
    };

}

#endif //SHADER_HPP
