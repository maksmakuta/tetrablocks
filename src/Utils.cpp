#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    void forXY(const glm::uvec2& size, const std::function<void(const glm::uvec2&)>& fn) {
        for (unsigned x = 0; x < size.x;x++) {
            for (unsigned y = 0; y < size.y;y++) {
                if (fn) fn({x,y});
            }
        }
    }

    std::string getAsset(const std::string& path) {
        return std::string(ASSETS_DIR) + path;
    }

}