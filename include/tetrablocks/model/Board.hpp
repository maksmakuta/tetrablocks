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
        explicit Board(const glm::uvec2& size = glm::uvec2{GRID_SIZE});

        bool isFit(const Shape&);
        void put(const Shape&);

        void checkLines();

        [[nodiscard]] glm::vec2 getSize() const;
        [[nodiscard]] std::vector<Block> getData() const;

    private:
        std::vector<Block> m_data;
        glm::u8vec2 m_size;
    };

}

#endif //BOARD_HPP
