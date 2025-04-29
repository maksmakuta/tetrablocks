#include "tetrablocks/graphics/Font.hpp"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "glad/gl.h"

namespace tetrablocks {

    Font::Font(const uint8_t size) : m_size(size){}

    void Font::load(const std::string &path, const std::initializer_list<glm::ivec2>& ranges) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)){
            std::cout << "Font: Cannot init Freetype library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face)) {
            std::cout << "Font: Cannot load Freetype face from path : " << path << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, m_size);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        long amount = 0;
        for (const auto& range : ranges) {
            amount += range.y - range.x;
        }
        const auto area = amount * (m_size * m_size);
        int side = 64;
        while (side * side < area) {
            side *= 2;
        }
        const auto tex = glm::vec2{static_cast<float>(side)};

        m_texture.alloc(side,side,TextureFormat::Mono);

        glm::ivec2 offset{1,1};
        int h = -1;

        for (const auto& range : ranges) {
            for (auto c = range.x; c <= range.y; c++) {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
                    std::cout << "Can't load glyph : " << c << std::endl;
                    continue;
                }

                if (offset.x + face->glyph->bitmap.width > side) {
                    offset.x = 1;
                    offset.y += h + 1;
                    h = -1;
                }

                m_texture.subdata(
                    offset.x,offset.y,
                    static_cast<int>(face->glyph->bitmap.width),
                    static_cast<int>(face->glyph->bitmap.rows),
                    TextureFormat::Mono,
                    face->glyph->bitmap.buffer
                );

                const glm::ivec2 size(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                const auto uv_a = glm::vec2(offset) / tex;
                const auto uv_b = glm::vec2(offset + size) / tex;

                Glyph character = {
                    glm::u8vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::i8vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<int>(face->glyph->advance.x >> 6),
                    uv_a, uv_b
                };
                m_glyphs.insert(std::make_pair(c, character));

                offset.x += static_cast<int>(face->glyph->bitmap.width) + 1;
                h = std::max(h,static_cast<int>(face->glyph->bitmap.rows));
            }
        }

        m_texture.genMipmaps();
        m_texture.setWrap(TextureWrap::ClampEdge);
        m_texture.setMinFilter(TextureFilter::Linear);
        m_texture.setMagFilter(TextureFilter::Linear);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void Font::clear() {
        m_glyphs.clear();
        m_texture.dealloc();
        m_size = 0;
    }

    int Font::width(const std::string& str) const {
        int result = 0;
        for (const auto& c : str) {
            if (const auto& g = at(c)) {
                result += g->advance;
            }
        }
        return result;
    }

    int Font::height(const std::string& str) const {
        int result = 0;
        for (const auto& c : str) {
            if (const auto& g = at(c)) {
                result = std::max<unsigned char>(g->size.y, result);
            }
        }
        return result;

    }

    std::optional<Glyph> Font::at(const int i) const{
        if (m_glyphs.contains(i)) {
            return m_glyphs.at(i);
        }
        return std::nullopt;
    }

    Texture Font::getTexture() const{
        return m_texture;
    }

    int Font::getSize() const {
        return m_size;
    }
}
