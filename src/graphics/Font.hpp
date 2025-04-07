#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <optional>
#include <string>
#include <glm/vec2.hpp>

#include "Texture.hpp"

namespace tetrablocks::graphics {

    using uint = glm::uint;

    struct Glyph {
        glm::uvec2 size;
        glm::ivec2 offset;
        uint advance;
        glm::vec2 uv_a;
        glm::vec2 uv_b;
    };

    class Font {
    public:
        Font() = default;

        void load(const std::string& font_path, uint size = 24);
        void clear();

        std::optional<Glyph> operator[](uint code);

        [[nodiscard]] Texture getTexture() const;
        [[nodiscard]] uint getSize() const;
    private:
        std::map<uint,Glyph> m_glyphs;
        Texture m_texture;
        uint m_size{0};
    };

}

#endif //FONT_HPP
