#include "tetrablocks/game/ShapeFactory.hpp"

namespace tetrablocks {

    ShapeFactory::ShapeFactory(const glm::uint seed) : m_generator(seed == 0 ? std::random_device{}() : seed) {}

    Shape ShapeFactory::getNext(){
        constexpr auto o = Block::Empty;
        const auto b = genColor();
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
        return shapes[m_generator() % shapes.size()];
    }

    Block ShapeFactory::genColor() {
        return static_cast<Block>(m_generator() % 7 + 1);
    }

}
