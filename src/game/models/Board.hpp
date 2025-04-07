#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <glm/vec2.hpp>

#include "Shape.hpp"

namespace tetrablocks::models {

    class Board {
    public:
        explicit Board(const glm::u8vec2& size = {9,9});

        void clear();
        void place(const Shape& shape, const glm::u8vec2& offset);
        [[nodiscard]] bool fit(const Shape& shape, const glm::u8vec2& offset) const;

        uint8_t operator[](const glm::u8vec2& pos) const;
        [[nodiscard]] glm::u8vec2 getSize() const;

    private:
        std::vector<uint8_t> m_board;
        glm::u8vec2 m_size;
    };

}

#endif //BOARD_HPP
