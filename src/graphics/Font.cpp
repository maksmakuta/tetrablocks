#include "tetrablocks/graphics/Font.hpp"
#include <iostream>

#include <ft2build.h>

#include "glad/gl.h"

#include FT_FREETYPE_H

namespace tetrablocks {

    Font::Font() = default;

    Font::~Font() {
        if (!Characters.empty()) {
            for (const auto&[_, c] : Characters) {
                glDeleteTextures(1,&c.TextureID);
            }
            Characters.clear();
        }
    }

    void Font::loadFont(const std::string &path, const int size) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)){
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, size);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 32; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
}
