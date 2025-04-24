#include "tetrablocks/model/Shape.hpp"

namespace tetrablocks {

    Shape::Shape() : m_blocks(1,Block::Empty), m_size(1,1) {}

    Shape::Shape(const glm::u8vec2& size, const std::vector<Block>& data) : m_blocks(data),m_size(size) {}

    Block& Shape::at(const glm::u8vec2& pos) {
        assert(pos.x < m_size.x && pos.y < m_size.y);
        return m_blocks[pos.x + pos.y * m_size.x];
    }

    std::vector<Block> Shape::getData() const {
        return m_blocks;
    }

    glm::u8vec2 Shape::getSize() const {
        return m_size;
    }

}
