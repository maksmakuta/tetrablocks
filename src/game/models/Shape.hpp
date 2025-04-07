#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cstdint>
#include <vector>
#include <glm/vec2.hpp>

namespace tetrablocks::models {

    class Shape {
    public:
        Shape() = default;
        Shape(const std::vector<uint8_t>& data, const glm::u8vec2& size);

        void set(const glm::u8vec2& pos, uint8_t value);

        uint8_t operator[](const glm::u8vec2& pos) const;
        [[nodiscard]] glm::u8vec2 getSize() const;

    private:
        std::vector<uint8_t> m_data;
        glm::u8vec2 m_size{0};
    };

}

#endif //SHAPE_HPP
