#include "tetrablocks/model/Block.hpp"

#include "tetrablocks/Constants.hpp"

namespace tetrablocks {

    glm::uint getColor(const Block& b) {
        switch (b) {
            case Block::Cyan:
                return 0xFF00FFFF;
            case Block::Yellow:
                return 0xFFFFFF00;
            case Block::Purple:
                return 0xFF800080;
            case Block::Green:
                return 0xFF00FF00;
            case Block::Red:
                return 0xFFFF0000;
            case Block::Blue:
                return 0xFF0000FF;
            case Block::Orange:
                return 0xFFFFA500;
            case Block::Empty:
                return COLOR_GRID_CELL;
        }
    }

}
