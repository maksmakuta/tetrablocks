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

    Shape Shape::getRandom(const uint id) {
        constexpr auto o = Block::Empty;
        const auto b = static_cast<Block>((id % 7 == 0 ? 1 : id % 7));
        const auto shapes = std::vector<Shape>{
            {
                {4, 1},
                {
                    b,b,b,b
                }
            },
            {
                    {1, 4},
                {
                    b,
                    b,
                    b,
                    b
                }
            },
            {
                {2, 2},
                {
                    b,b,
                    b,b
                }
            },
            {
                {2, 3},
                {
                    b,o,
                    b,b,
                    o,b
                }
            },
            {
                {2, 3},
                {
                    o,b,
                    b,b,
                    b,o
                }
            },
            {
                {3, 2},
                {
                    o,b,b,
                    b,b,o
                }
            },
            {
                {3, 2},
                {
                    b,b,o,
                    o,b,b
                }
            },
            {
                {3, 2},
                {
                    b,b,b,
                    b,o,o
                }
            },
            {
                {3, 2},
                {
                    b,b,b,
                    o,o,b
                }
            },
            {
                {2, 3},
                {
                    b,b,
                    b,o,
                    b,o
                }
            },
            {
                {2, 3},
                {
                    b,o,
                    b,o,
                    b,b
                }
            },
            {
                {2, 3},
                {
                    b,o,
                    b,b,
                    b,o
                }
            },
            {
                {2, 3},
                {
                    o,b,
                    b,b,
                    o,b
                }
            },
            {
                {3, 2},
                {
                    o,b,o,
                    b,b,b
                }
            },
            {
                {3, 2},
                {
                    b,b,b,
                    o,b,o
                }
            },
            {
                    {3, 2},
                    {
                        b,o,o,
                        b,b,b,
                    }
            },
            {
                    {3, 2},
                    {
                        o,o,b,
                        b,b,b
                    }
            },
            {
                    {2, 3},
                    {
                        b,b,
                        o,b,
                        o,b
                    }
            },
            {
                    {2, 3},
                    {
                        o,b,
                        o,b,
                        b,b
                    }
            }
        };
        return shapes[id % shapes.size()];
    }
}
