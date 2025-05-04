#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <glm/vec2.hpp>

#include "Block.hpp"

namespace tetrablocks {

    class Shape {
    public:
        Shape();
        Shape(const glm::u8vec2& size, const std::vector<Block>& data);

        Block& at(const glm::u8vec2&);

        std::vector<glm::u8vec2> getVisible();
        [[nodiscard]] std::vector<Block> getData() const;
        [[nodiscard]] glm::u8vec2 getSize() const;

    private:
        std::vector<Block> m_blocks;
        glm::u8vec2 m_size;
    };
}

#endif //SHAPE_HPP
