#include "Shape.hpp"

namespace tetrablocks::models {

    Shape::Shape(
        const std::vector<uint8_t>& data,
        const glm::u8vec2& size
    ) : m_data(data), m_size(size) {}

    void Shape::set(const glm::u8vec2& pos, uint8_t value) {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            m_data[pos.x + m_size.x * pos.y] = value;
        }
    }

    uint8_t Shape::operator[](const glm::u8vec2& pos) const {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            return m_data[pos.x + m_size.x * pos.y];
        }
        return 0;
    }

    glm::u8vec2 Shape::getSize() const {
        return m_size;
    }

}