#ifndef FONT_HPP
#define FONT_HPP
#include <map>
#include <string>
#include <glm/vec2.hpp>

namespace tetrablocks {

    class Font {
    public:
        Font();
        ~Font();

        void loadFont(const std::string& path, int size = 24);

        struct Character {
            unsigned int TextureID; // ID handle of the glyph texture
            glm::ivec2   Size;      // Size of glyph
            glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
            unsigned int Advance;   // Horizontal offset to advance to next glyph
        };

        std::map<char, Character> Characters;
    };

}

#endif //FONT_HPP
