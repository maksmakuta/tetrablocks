#ifndef SHAPERENDERER_HPP
#define SHAPERENDERER_HPP

#include <vector>
#include <glm/mat4x4.hpp>

#include "graphics/Shader.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::render {

    struct ShapeVertex {
        uint pos;
        uint col;

        ShapeVertex(const glm::vec2& p, const uint c)
            : pos( static_cast<uint>(p.y) << 16 | static_cast<uint>(p.x)), col(c){}
    };

    class ShapeRenderer {
    public:
        ShapeRenderer() = default;

        void init(const utils::Assets& assets);
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
        std::pmr::vector<ShapeVertex> m_data;
        graphics::Shader m_shader;
        uint m_VAO{0}, m_VBO{0};
        float m_width = 1.f;
        uint m_color = 0xFFFFFFFF;
        bool m_fill = true;
    };

}

#endif //SHAPERENDERER_HPP
