#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <optional>
#include <string>
#include <glm/vec2.hpp>

#include "Texture.hpp"

namespace tetrablocks {

    struct Glyph {
        glm::uvec2 size;
        glm::ivec2 offset;
        glm::uint advance;
        glm::vec2 uv_a;
        glm::vec2 uv_b;
    };

    class Font {
    public:
        explicit Font(const std::string& font_path, glm::uint size = 32);

        std::optional<Glyph> operator[](uint code) const;

        [[nodiscard]] float getWidth(const std::string& text) const;
        [[nodiscard]] Texture getTexture() const;
        [[nodiscard]] uint getSize() const;
    private:
        std::map<uint,Glyph> m_glyphs;
        Texture m_texture;
        uint m_size{0};
    };

}

#endif //FONT_HPP
