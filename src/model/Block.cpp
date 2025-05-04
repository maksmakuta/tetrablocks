#include "tetrablocks/model/Block.hpp"

#include "tetrablocks/Constants.hpp"

namespace tetrablocks {

    glm::uint getColor(const Block& b) {
        switch (b) {
            case Block::Cyan:
                return 0xFF00FFFF;
            case Block::Yellow:
                return 0xFFFFFF33;
            case Block::Purple:
                return 0xFFFF33FF;
            case Block::Green:
                return 0xFF39FF14;
            case Block::Red:
                return 0xFFFF073A;
            case Block::Blue:
                return 0xFF1E90FF;
            case Block::Orange:
                return 0xFFFF5F1F;
            case Block::Empty:
                return COLOR_GRID_CELL;
        }
    }

}
