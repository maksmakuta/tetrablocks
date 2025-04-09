#ifndef COLOR_HPP
#define COLOR_HPP

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace tetrablocks::graphics {

    class Color {
    public:
        Color() = default;
        explicit Color(glm::uint hex);
        explicit Color(const glm::vec3& _vec3);
        explicit Color(const glm::vec4& _vec4);
        Color(float red,float green,float blue,float alpha = 1.f);

        [[nodiscard]] float getRed() const;
        [[nodiscard]] float getGreen() const;
        [[nodiscard]] float getBlue() const;
        [[nodiscard]] float getAlpha() const;

        [[nodiscard]] uint8_t getIRed() const;
        [[nodiscard]] uint8_t getIGreen() const;
        [[nodiscard]] uint8_t getIBlue() const;
        [[nodiscard]] uint8_t getIAlpha() const;

        [[nodiscard]] glm::uint toHex() const;
        [[nodiscard]] glm::vec3 toVec3() const;
        [[nodiscard]] glm::vec4 toVec4() const;
    private:
        glm::uint m_color{0};
    };

}

#endif //COLOR_HPP
