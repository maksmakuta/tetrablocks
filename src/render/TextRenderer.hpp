#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <string>
#include <vector>

#include "graphics/Font.hpp"
#include "graphics/Shader.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::render {

    struct TextVertex {
        uint pos;
        uint tex;

        TextVertex(const glm::vec2& p, const glm::vec2& t) {
            pos = static_cast<uint>(p.y) << 16 | static_cast<uint>(p.x);
            tex = static_cast<uint>(t.y* UINT16_MAX) << 16 | static_cast<uint>(t.x * UINT16_MAX);
        }
    };

    class TextRenderer {
    public:
        TextRenderer() = default;

        void init(const utils::Assets& assets,const std::string& name, uint size = 24);
        void clear();

        void text(const std::string& text, const glm::vec2& pos);
        void draw(const glm::mat4& proj);
    private:
        uint m_VAO{0},m_VBO{0};
        graphics::Font m_font;
        graphics::Shader m_shader;
        std::vector<TextVertex> m_data;
    };

}

#endif //TEXTRENDERER_HPP
