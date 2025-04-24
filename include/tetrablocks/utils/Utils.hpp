#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <glm/vec2.hpp>

namespace tetrablocks {

    inline void forXY(const glm::uvec2& size, const std::function<void(const glm::uvec2&)>& fn) {
        for (unsigned x = 0; x < size.x;x++) {
            for (unsigned y = 0; y < size.y;y++) {
                if (fn) fn({x,y});
            }
        }
    }

}

#endif //UTILS_HPP
