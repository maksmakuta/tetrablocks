#include "Font.hpp"

#include <format>
#include <stdexcept>

#include <ft2build.h>
#include <iostream>

#include "gl/gl.h"

#include FT_FREETYPE_H

namespace tetrablocks::graphics {

    void Font::load(const std::string& font_path, const uint size) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            throw std::runtime_error("Failed to initialize FreeType");

        FT_Face face;
        if (FT_New_Face(ft, font_path.c_str(), 0, &face))
            throw std::runtime_error("Failed to load font: " + font_path);

        FT_Set_Pixel_Sizes(face, 0, size);
        m_size = size;

        const int startIndex = 32;
        const int endIndex = 128;
        const int range = endIndex - startIndex;

        const int area = static_cast<int>(size * size) * range;
        int side = 64;
        while (side * side < area) {
            side *= 2;
        }

        m_texture.alloc(side,side,TextureFormat::Mono,nullptr);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        glm::ivec2 off{0,0};
        int height = -1;

        for (unsigned char c = startIndex; c < endIndex; c++){
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            if (off.x + face->glyph->bitmap.width > side) {
                off.x = 0;
                off.y += height + 1;
                height = -1;
            }

            m_texture.subdata(
                off.x,
                off.y,
                static_cast<int>(face->glyph->bitmap.width),
                static_cast<int>(face->glyph->bitmap.rows),
                TextureFormat::Mono,
                face->glyph->bitmap.buffer
            );

            Glyph character{
                glm::uvec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<uint>(face->glyph->advance.x >> 6),
                {},{}
            };

            m_glyphs.insert_or_assign(c,character);

            off.x += static_cast<int>(face->glyph->bitmap.width) + 1;
            height = std::max<int>(height,static_cast<int>(face->glyph->bitmap.rows));

            std::cout << std::format("[{}] -> ({},{})\n", char(c), off.x, off.y);
        }

        m_texture.genMipmaps();

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

    }

    void Font::clear() {
        m_glyphs.clear();
        m_texture.clear();
        m_size = 0;
    }

    std::optional<Glyph> Font::operator[](const uint code) {
        if (m_glyphs.contains(code)) {
            return m_glyphs.at(code);
        }
        return std::nullopt;
    }

    Texture Font::getTexture() const {
        return m_texture;
    }

    uint Font::getSize() const {
        return m_size;
    }

}