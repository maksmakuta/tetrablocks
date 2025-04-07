#include "Board.hpp"

#include <algorithm>

namespace tetrablocks::models {

    Board::Board(const glm::u8vec2& size) : m_board(size.x * size.y, 0), m_size(size) {}

    void Board::clear() {
        std::ranges::fill(m_board,0);
    }

    void Board::place(const Shape &shape, const glm::u8vec2 &offset) {
        if (offset.x + shape.getSize().x < m_size.x && offset.y + shape.getSize().y < m_size.y) {
            for (uint8_t x = 0; x < shape.getSize().x; x++) {
                for (uint8_t y = 0; y < shape.getSize().y; y++) {
                    const auto v = glm::u8vec2(x,y);
                    const auto pos = offset + v;
                    m_board[pos.x + m_size.x * pos.y] = shape[v];
                }
            }
        }
    }

    bool Board::fit(const Shape& shape, const glm::u8vec2& offset) const {
        if (offset.x + shape.getSize().x < m_size.x && offset.y + shape.getSize().y < m_size.y) {
            for (uint8_t x = 0; x < shape.getSize().x; x++) {
                for (uint8_t y = 0; y < shape.getSize().y; y++) {
                    const auto v = glm::u8vec2(x,y);
                    if (shape[{x,y}] == 0)
                        continue;
                    if (this->operator[](offset + v) != 0)
                        return false;
                }
            }
            return true;
        }
        return false;
    }

    uint8_t Board::operator[](const glm::u8vec2& pos) const {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            return m_board[pos.x + m_size.x * pos.y];
        }
        return 0;
    }

    glm::u8vec2 Board::getSize() const {
        return m_size;
    }

}
