#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace tetrablocks {

    void forXY(const glm::uvec2& size, const std::function<void(const glm::uvec2&)>& fn);
    std::string getAsset(const std::string& path);

    glm::vec2 random(const glm::vec2& min = {-1,-1}, const glm::vec2& max = {1,1});
    glm::uint randColor();

    bool inRect(const glm::vec4& rect, const glm::vec2& point);

}

#endif //UTILS_HPP
