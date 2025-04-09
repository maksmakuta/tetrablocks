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

        const glm::vec2 atlas{static_cast<float>(side)};

        m_texture.alloc(side,side,TextureFormat::Mono,nullptr);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glm::ivec2 off{1,1};
        int height = -1;

        for (unsigned char c = startIndex; c < endIndex; c++){
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            if (off.x + face->glyph->bitmap.width > side) {
                off.x = 1;
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

            Glyph character{};
            character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            character.offset = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            character.advance = static_cast<uint>(face->glyph->advance.x >> 6);
            character.uv_a = glm::vec2(off) / atlas;
            character.uv_b = glm::vec2(off + glm::ivec2(character.size)) / atlas;

            m_glyphs.insert_or_assign(c,character);

            off.x += static_cast<int>(face->glyph->bitmap.width) + 1;
            height = std::max<int>(height,static_cast<int>(face->glyph->bitmap.rows));
        }

        m_texture.setMagFilter(TextureFilter::Linear);
        m_texture.setMinFilter(TextureFilter::Nearest);
        m_texture.genMipmaps();

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

    }

    void Font::deinit() {
        m_glyphs.clear();
        m_texture.deinit();
        m_size = 0;
    }

    std::optional<Glyph> Font::operator[](const uint code) const {
        if (m_glyphs.contains(code)) {
            return m_glyphs.at(code);
        }
        return std::nullopt;
    }

    float Font::getWidth(const std::string &text) const {
        float t = 0;
        for (const auto& c : text) {
            if (const auto g = operator[](c); g) {
                t += static_cast<float>(g->advance);
            }
        }
        return t;
    }

    Texture Font::getTexture() const {
        return m_texture;
    }

    uint Font::getSize() const {
        return m_size;
    }

}