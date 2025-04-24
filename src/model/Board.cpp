#include "tetrablocks/model/Board.hpp"

namespace tetrablocks {

    Board::Board(const glm::uvec2& size) : m_data(size.x * size.y), m_size(size){}

    bool Board::isFit(const Shape&) {
        //TODO(Board::isFit(const Shape&))
        return false;
    }

    void Board::put(const Shape&) {
        //TODO(Board::put(const Shape&))
    }

    void Board::checkLines() {
        //TODO(Board::checkLines())
    }

    glm::vec2 Board::getSize() const {
        return m_size;
    }

    std::vector<Block> Board::getData() const {
        return m_data;
    }
}