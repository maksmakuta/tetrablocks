#include "TextRenderer.hpp"

#include "graphics/gl/gl.h"

namespace tetrablocks::render {

    namespace detail {

        void loadShaders(graphics::Shader& s,const utils::Assets& assets, const std::string& name) {
            s.fromFiles(
                assets.getShader(name + ".vert"),
                assets.getShader(name + ".frag")
            );
        }

    }

    void TextRenderer::init(const utils::Assets& assets,const std::string& name, const uint size) {
        detail::loadShaders(m_shader,assets,"text");
        m_font.load(assets.getFont(name),size);

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(TextVertex), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(TextVertex), reinterpret_cast<void *>((offsetof(TextVertex, tex))));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void TextRenderer::clear() {
        m_shader.clear();
        m_font.clear();
        m_data.clear();
    }

    void TextRenderer::text(const std::string &text, const glm::vec2 &pos) {
        glm::ivec2 p = pos;
        for (const auto& c : text) {
            if (const auto glyph = m_font[c]; glyph) {

                const uint x = p.x + glyph->offset.x;
                const uint y = p.y - glyph->offset.y;
                const auto w = glyph->size.x;
                const auto h = glyph->size.y;

                const auto vertices = std::vector<TextVertex>{
                    { {x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y} },
                    { {x,     y    },   {glyph->uv_a.x,glyph->uv_a.y} },
                    { {x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y} },

                    { {x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y} },
                    { {x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y} },
                    { {x + w, y + h},   {glyph->uv_b.x,glyph->uv_b.y} }
                };

                m_data.insert(m_data.end(),vertices.begin(), vertices.end());
                p.x += glyph->advance;
            }
        }
    }

    void TextRenderer::draw(const glm::mat4& proj) {
        m_font.getTexture().bind();

        glUseProgram(m_shader.handle());

        m_shader.setMat4("proj",proj);
        m_shader.setInt("u_image",0);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(TextVertex) * m_data.size()), m_data.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_data.size()));
        glBindVertexArray(0);

        m_data.clear();
    }
}
