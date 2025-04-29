#include "tetrablocks/Utils.hpp"

#include <random>

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

    glm::vec2 random(const glm::vec2& min, const glm::vec2& max) {
        std::random_device rd;
        std::uniform_real_distribution ux{min.x, max.x};
        std::uniform_real_distribution uy{min.y, max.y};
        return {ux(rd),uy(rd)};
    }

    glm::uint randColor() {
        std::random_device rd;
        std::uniform_int_distribution u{0,255};
        return (0xFF << 24) | (u(rd) << 16) | (u(rd) << 8) | u(rd);
    }

    bool inRect(const glm::vec4 &rect, const glm::vec2 &point) {
        const auto a = glm::vec2{rect.x,rect.y};
        const auto b = a + glm::vec2{rect.z,rect.w};
        return point.x >= a.x && point.x <= b.x && point.y >= a.y && point.y <= b.y;
    }
}
