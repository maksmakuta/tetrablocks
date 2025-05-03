#include "tetrablocks/model/Board.hpp"

#include <algorithm>
#include <glm/fwd.hpp>

#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Board::Board(const glm::u8vec2& size) : m_data(size.x * size.y), m_size(size){}

    bool Board::isFit(Shape& s, const glm::u8vec2& offset) {
        if (offset + s.getSize() <= getSize()) {
            return std::ranges::all_of(s.getVisible(),[&offset, this](const glm::u8vec2& item) {
                return at(offset + item) == Block::Empty;
            });
        }
        return false;
    }

    void Board::put(Shape& s, const glm::u8vec2& offset) {
        forXY(s.getSize(),[this, &offset, &s](const glm::u8vec2& p) {
            const auto pos = offset + p;
            if (at(pos) == Block::Empty && s.at(p) != Block::Empty) {
                at(pos) = s.at(p);
            }
        });
    }

    int Board::checkLines() {
        int lines = 0;
        //TODO(Board::checkLines())
        return lines;
    }

    glm::u8vec2 Board::getSize() const {
        return m_size;
    }

    std::vector<Block> Board::getData() const {
        return m_data;
    }

    Block& Board::at(const glm::u8vec2 &pos) {
        return m_data[pos.x + pos.y * m_size.x];
    }

}
