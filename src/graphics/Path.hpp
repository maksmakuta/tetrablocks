#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <glm/vec2.hpp>

namespace tetrablocks::graphics {

    class Path {
    public:
        Path() = default;
        explicit Path(const std::vector<glm::vec2>&);

        void moveTo(const glm::vec2&);
        void lineTo(const glm::vec2&);
        void end();

        [[nodiscard]] std::size_t length() const;
        glm::vec2 operator[](std::size_t) const;

    private:
        std::vector<glm::vec2> m_data;
    };

}

#endif //PATH_HPP
