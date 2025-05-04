#include "tetrablocks/model/Shape.hpp"

#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Shape::Shape() : m_blocks(0), m_size(0,0) {}

    Shape::Shape(const glm::u8vec2& size, const std::vector<Block>& data) : m_blocks(data),m_size(size) {}

    Block& Shape::at(const glm::u8vec2& pos) {
        return m_blocks[pos.x + pos.y * m_size.x];
    }

    std::vector<glm::u8vec2> Shape::getVisible() {
        auto result = std::vector<glm::u8vec2>();
        forXY(getSize(),[this,&result](const glm::u8vec2& p) {
            if (at(p) != Block::Empty) {
                result.emplace_back(p);
            }
        });
        return result;
    }

    std::vector<Block> Shape::getData() const {
        return m_blocks;
    }

    glm::u8vec2 Shape::getSize() const {
        return m_size;
    }
}
