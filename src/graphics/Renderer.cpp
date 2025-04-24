#include "tetrablocks/graphics/Renderer.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"
#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Renderer::Renderer() : m_vao(0), m_vbo(0), m_color(0xFF000000), m_texture(0), m_type(1) {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, tex)));
        glEnableVertexAttribArray(1);

        m_shader.loadFromFiles(
            getAsset("/shaders/main.vert"),
            getAsset("/shaders/main.frag")
        );
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void Renderer::resize(const int w, const int h) {
        glViewport(0,0,w,h);
        m_matrix = glm::ortho(0.f,static_cast<float>(w),static_cast<float>(h),0.f);
    }

    void Renderer::clear(const glm::uint &color) {
        glClearColor(
            static_cast<float>(color >> 16 & 0xFF) / 255.f,
            static_cast<float>(color >> 8  & 0xFF) / 255.f,
            static_cast<float>(color >> 0  & 0xFF) / 255.f,
            static_cast<float>(color >> 24 & 0xFF) / 255.f
        );
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::drawText(const Font& fnt, const std::string& text, const glm::vec2& pos, const glm::uint& col, const Align& align) {
        glm::vec2 p = pos;

        if (align == Align::Center) {
            p.x += fnt.getWidth(text) / 2.f;
        }
        if (align == Align::End) {
            p.x += fnt.getWidth(text);
        }

        for (const auto& c : text) {
            if (const auto glyph = fnt[c]) {

                const auto x = p.x + static_cast<float>(glyph->offset.x);
                const auto y = p.y - static_cast<float>(glyph->offset.y);
                const auto w = static_cast<float>(glyph->size.x);
                const auto h = static_cast<float>(glyph->size.y);

                const auto vertices = std::vector<Vertex>{
                            { glm::vec2{x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y}},
                            { glm::vec2{x,     y    },   {glyph->uv_a.x,glyph->uv_a.y}},
                            { glm::vec2{x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y}},
                            { glm::vec2{x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y}},
                            { glm::vec2{x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y}},
                            { glm::vec2{x + w, y + h},   {glyph->uv_b.x,glyph->uv_b.y}}
                };

                m_vertices.insert(m_vertices.end(),vertices.begin(), vertices.end());
                p.x += static_cast<float>(glyph->advance);
            }
        }

        fnt.getTexture().bind();
        m_type = 3;
        m_texture = 0;
        m_color = col;

        push();
    }

    void Renderer::drawRect(const float x, const float y, const float w, const float h, const glm::uint& col) {
        constexpr auto zero = glm::vec2{0};
        const auto vertices = std::vector<Vertex>{
            { glm::vec2{x,     y + h},zero},
            { glm::vec2{x,     y    },zero},
            { glm::vec2{x + w, y    },zero},
            { glm::vec2{x,     y + h},zero},
            { glm::vec2{x + w, y    },zero},
            { glm::vec2{x + w, y + h},zero}
        };
        m_vertices.insert(m_vertices.end(),vertices.begin(), vertices.end());

        m_type = 1;
        m_color = col;

        push();
    }

    void Renderer::drawImage(const float x, const float y, const float w, const float h,  const Texture& tex) {
        const auto vertices = std::vector<Vertex>{
                { glm::vec2{x,     y + h},   {0.f,1.f}},
                { glm::vec2{x,     y    },   {0.f,0.f}},
                { glm::vec2{x + w, y    },   {1.f,0.f}},
                { glm::vec2{x,     y + h},   {0.f,1.f}},
                { glm::vec2{x + w, y    },   {1.f,0.f}},
                { glm::vec2{x + w, y + h},   {1.f,1.f}}
        };
        m_vertices.insert(m_vertices.end(),vertices.begin(), vertices.end());

        m_type = 2;
        tex.bind();
        m_texture = 0;

        push();
    }

    void Renderer::push() {
        m_shader.use();
        m_shader.setMat4("u_mat",m_matrix);
        m_shader.setInt("u_type",m_type);
        if (m_type == 1) {
            const glm::vec4 col{
                static_cast<float>(m_color >> 16 & 0xFF) / 255.f,
                static_cast<float>(m_color >> 8  & 0xFF) / 255.f,
                static_cast<float>(m_color >> 0  & 0xFF) / 255.f,
                static_cast<float>(m_color >> 24 & 0xFF) / 255.f,
            };
            m_shader.setVec4("u_color",col);
        }else {
            m_shader.setInt("u_image",m_texture);
        }

        if (m_type == 3) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(m_vertices.size() * sizeof(Vertex)), m_vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));

        if (m_type == 3) {
            glDisable(GL_BLEND);
        }

        m_vertices.clear();
    }
}
