#include "tetrablocks/model/Board.hpp"
#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Board::Board(const glm::uvec2& size) : m_data(size.x * size.y), m_size(size){}

    bool Board::isFit(Shape& s, const glm::u8vec2& offset) {
        if (offset + s.getSize() < getSize()) {
            auto res = true;
            forXY(s.getSize(),[this, &offset, &s, &res](const glm::u8vec2& p) {
                const auto pos = offset + p;
                if (!(at(pos) == Block::Empty && s.at(p) != Block::Empty) && res) {
                    res = false;
                }
            });
            return res;
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

        for (int x = 0; x < m_size.x; x++) {
            if (isFull(x,true)) {
                clear(x,true);
                ++lines;
            }
            if (isFull(x,false)) {
                clear(x,false);
                ++lines;
            }
        }
        return lines;
    }

    glm::u8vec2 Board::getSize() const {
        return m_size;
    }

    std::vector<Block> Board::getData() const {
        return m_data;
    }

    Block& Board::at(const glm::ivec2 &pos) {
        assert(pos.x < m_size.x && pos.y < m_size.y);
        return m_data[pos.x + m_size.x * pos.y];
    }

    bool Board::isFull(const int pos, const bool h) {
        for (int t = 0; t < h ? m_size.x : m_size.y; t++) {
            if (at(h ? glm::vec2{t,pos} : glm::vec2{pos, t}) == Block::Empty) {
                return false;
            }
        }
        return true;
    }

    void Board::clear(const int pos, const bool h) {
        for (int t = 0; t < h ? m_size.x : m_size.y; t++) {
            at(h ? glm::vec2{t,pos} : glm::vec2{pos, t}) = Block::Empty;
        }
    }
}
