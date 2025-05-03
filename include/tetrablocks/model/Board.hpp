#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <glm/vec2.hpp>

#include "Block.hpp"
#include "Shape.hpp"
#include "tetrablocks/Constants.hpp"

namespace tetrablocks {

    class Board {
    public:
        explicit Board(const glm::u8vec2& size = glm::u8vec2{GRID_SIZE});

        bool isFit(Shape&, const glm::u8vec2& offset);
        void put(Shape&, const glm::u8vec2& offset);

        int checkLines();

        [[nodiscard]] glm::u8vec2 getSize() const;
        [[nodiscard]] std::vector<Block> getData() const;
        Block& at(const glm::u8vec2& pos);

    private:
        std::vector<Block> m_data;
        glm::u8vec2 m_size;
    };

}

#endif //BOARD_HPP
