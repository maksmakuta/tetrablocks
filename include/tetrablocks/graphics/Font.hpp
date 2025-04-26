#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <optional>
#include <string>
#include <glm/vec2.hpp>

#include "Texture.hpp"

namespace tetrablocks {

    namespace Codepoint {
        constexpr auto Latin = glm::ivec2{32,127};
    }

    enum class Align : uint8_t{
        Center,
        Start,
        End
    };

    struct Glyph {
        glm::u8vec2 size;
        glm::i8vec2 offset;
        int advance;
        glm::vec2 uv_a;
        glm::vec2 uv_b;
    };

    class Font {
    public:
        explicit Font(uint8_t size = 24);
        void load(
            const std::string& path,
            const std::initializer_list<glm::ivec2>& codepoints = { Codepoint::Latin }
        );
        std::optional<Glyph> at(int i);

    private:
        std::map<int, Glyph> m_glyphs;
        Texture m_texture;
        uint8_t m_size;
    };

}

#endif //FONT_HPP
