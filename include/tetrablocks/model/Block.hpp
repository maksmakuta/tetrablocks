#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/common.hpp>

namespace tetrablocks {

    using byte = unsigned char;

    enum class Block : byte{
        Empty = 0,
        Cyan,
        Yellow,
        Purple,
        Green,
        Red,
        Blue,
        Orange
    };

    glm::uint getColor(const Block&);
}

#endif //BLOCK_HPP
