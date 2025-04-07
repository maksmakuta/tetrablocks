#ifndef SHAPERENDERER_HPP
#define SHAPERENDERER_HPP

#include <vector>
#include <glm/mat4x4.hpp>

#include "graphics/Shader.hpp"

namespace tetrablocks::render {

    struct ShapeVertex {
        uint pos;
        uint col;
    };

    class ShapeRenderer {
    public:
        ShapeRenderer() = default;

        void init();
        void clear();

        void fill();
        void stroke();
        void setColor(uint hex);
        void setThickness(float value);

        void line(const glm::vec2& a,const glm::vec2& b);
        void triangle(const glm::vec2& a,const glm::vec2& b, const glm::vec2& c);
        void square(const glm::vec2& a, float size);
        void rect(const glm::vec2& origin,const glm::vec2& size);

        void draw(const glm::mat4& proj);

    private:
        uint m_VAO{0}, m_VBO{0};
        graphics::Shader m_shader;
        std::pmr::vector<ShapeVertex> m_data;
    };

}

#endif //SHAPERENDERER_HPP
