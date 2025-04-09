#include "Path.hpp"

namespace tetrablocks::graphics {

    constexpr auto PATH_END = glm::vec2{std::numeric_limits<float>::infinity()};

    Path::Path(const Path& p) = default;

    void Path::moveTo(const glm::vec2& p) {
        if (m_data.back() != PATH_END) {
            end();
        }
        m_data.push_back(p);
    }

    void Path::lineTo(const glm::vec2& p) {
        m_data.push_back(p);
    }

    void Path::end() {
        m_data.push_back(PATH_END);
    }

    std::size_t Path::length() const {
        return m_data.size();
    }
}
