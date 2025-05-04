#include "tetrablocks/model/Board.hpp"

#include <algorithm>
#include <glm/fwd.hpp>

#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Board::Board(const glm::u8vec2& size) : m_data(size.x * size.y), m_size(size){}

    bool Board::fit(Shape& s) {
        if (s.getSize() < glm::u8vec2{1})
            return false;
        for (int y = 0; y < m_size.y; ++y) {
            for (int x = 0; x < m_size.x; ++x) {
                if (at({x,y}) == Block::Empty) {
                    if (isFit(s,{x,y})) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

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

        std::vector clearRows(m_size.y, true);
        std::vector clearCols(m_size.x, true);

        for (int y = 0; y < m_size.y; ++y) {
            for (int x = 0; x < m_size.x; ++x) {
                if (m_data[y * m_size.x + x] == Block::Empty) {
                    clearRows[y] = false;
                    clearCols[x] = false;
                }
            }
        }

        for (int y = 0; y < m_size.y; ++y) {
            if (clearRows[y]) {
                ++lines;
                for (int x = 0; x < m_size.x; ++x) {
                    m_data[y * m_size.x + x] = Block::Empty;
                }
            }
        }

        for (int x = 0; x < m_size.x; ++x) {
            if (clearCols[x]) {
                ++lines;
                for (int y = 0; y < m_size.y; ++y) {
                    m_data[y * m_size.x + x] = Block::Empty;
                }
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

    Block& Board::at(const glm::u8vec2 &pos) {
        return m_data[pos.x + pos.y * m_size.x];
    }

}
