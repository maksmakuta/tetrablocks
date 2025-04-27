#include "tetrablocks/graphics/Renderer.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"
#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    constexpr auto TEX_RES = glm::vec2{std::numeric_limits<uint16_t>::max()};

    glm::mat4 toMat4(const OrthoMatrix& mat) {
        glm::mat4 result(1.0f);

        result[0][0] = mat.first.x;
        result[1][1] = mat.first.y;
        result[2][2] = mat.first.z;

        result[3][0] = mat.second.x;
        result[3][1] = mat.second.y;
        result[3][2] = mat.second.z;

        return result;
    }

    Vertex::Vertex(const int type, const glm::vec2& pos, const glm::uint& color, const glm::vec2& uv) {
        const auto posX = static_cast<uint16_t>(pos.x + (1 << 14));
        const auto posY = static_cast<uint16_t>(pos.y + (1 << 14));

        pos_type = (static_cast<glm::uint>(type & 0b11) << 30) |
                   (static_cast<uint16_t>(posX) << 15) |
                   (static_cast<uint16_t>(posY));

        col = color;

        const auto uvX = static_cast<uint16_t>(uv.x * static_cast<float>(0xFFFF));
        const auto uvY = static_cast<uint16_t>(uv.y * static_cast<float>(0xFFFF));

        tex = (static_cast<glm::uint>(uvX) << 16) |
              (static_cast<glm::uint>(uvY));
    }

    Renderer::Renderer() : m_data(1024), m_uv(0, 0, 1, 1), m_vao(0), m_vbo(0), m_color(0), m_paint(0) {
        m_shader.loadFromFiles(
            getAsset("/shaders/main.vert"),
            getAsset("/shaders/main.frag")
        );
        m_shader.use();

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(m_data.capacity() * sizeof(Vertex)), nullptr, GL_DYNAMIC_COPY);
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, col)));
        glEnableVertexAttribArray(2);
        glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, tex)));
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

    Renderer::~Renderer() = default;

    void Renderer::resize(const int w, const int h) {
        glViewport(0,0,w,h);

        glm::vec3 scales{
            2.f / static_cast<float>(w),
            2.f / static_cast<float>(-h),
            2.f,
        };

        glm::vec3 offsets{
            -1,
            1,
            -1,
        };

        m_matrix = std::make_pair(scales, offsets);
        m_shader.setMat4("u_mat",toMat4(m_matrix));

    }

    void Renderer::clear(const glm::uint &color) {
        glClearColor(
            static_cast<float>(color >> 16 & 0xFF) / 255.f,
            static_cast<float>(color >> 8  & 0xFF) / 255.f,
            static_cast<float>(color >> 0  & 0xFF) / 255.f,
            static_cast<float>(color >> 24 & 0xFF) / 255.f
        );
    }

    void Renderer::beginFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::endFrame() {
        flush();
    }

    void Renderer::fill(const glm::uint& col) {
        if (m_paint != 1) {
            flush();
            m_paint = 1;
        }
        m_color = col;
    }

    void Renderer::image(const Texture& tex, const glm::vec2& uv_a, const glm::vec2& uv_b) {
        if (m_paint != 2) {
            flush();
            m_paint = 2;
        }
        glBindTexture(GL_TEXTURE_2D,tex.getID());
        m_shader.setInt("u_image",0);
        m_uv = {uv_a,uv_b};
    }

    void Renderer::rect(const float x, const float y, const float w, const float h) {
        m_data.insert(m_data.end(),{
            Vertex(m_paint,{x  ,y  },m_color,{m_uv.x,m_uv.y}),
            Vertex(m_paint,{x+w,y  },m_color,{m_uv.z,m_uv.y}),
            Vertex(m_paint,{x+w,y+h},m_color,{m_uv.z,m_uv.w}),

            Vertex(m_paint,{x  ,y  },m_color,{m_uv.x,m_uv.y}),
            Vertex(m_paint,{x+w,y+h},m_color,{m_uv.z,m_uv.w}),
            Vertex(m_paint,{x  ,y+h},m_color,{m_uv.x,m_uv.w}),
        });
    }

    void Renderer::text(const Font& fnt, const std::string& text, const glm::vec2& pos, const Align&) {
        if (m_paint != 3) {
            flush();
            m_paint = 3;
        }
        glBindTexture(GL_TEXTURE_2D,fnt.getTexture().getID());
        m_shader.setInt("u_image",0);

        glm::vec2 p = pos;

        for(const auto& c : text) {
            if (const auto g = fnt.at(c); g.has_value()) {

                const float x = p.x + static_cast<float>(g->offset.x);
                const float y = p.y - static_cast<float>(g->offset.y);
                const float w = g->size.x;
                const float h = g->size.y;

                m_data.insert(m_data.end(),{
                    Vertex(m_paint,{x  ,y  },m_color,{g->uv_a.x,g->uv_a.y}),
                    Vertex(m_paint,{x+w,y  },m_color,{g->uv_b.x,g->uv_a.y}),
                    Vertex(m_paint,{x+w,y+h},m_color,{g->uv_b.x,g->uv_b.y}),

                    Vertex(m_paint,{x  ,y  },m_color,{g->uv_a.x,g->uv_a.y}),
                    Vertex(m_paint,{x+w,y+h},m_color,{g->uv_b.x,g->uv_b.y}),
                    Vertex(m_paint,{x  ,y+h},m_color,{g->uv_a.x,g->uv_b.y}),
                });

                p.x += static_cast<float>(g->advance);
            }
        }
    }

    void Renderer::flush() {
        if (m_data.empty() || m_paint == 0)
            return;

        if (m_paint == 3) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(m_data.size() * sizeof(Vertex)), m_data.data(), GL_DYNAMIC_COPY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_data.size()));

        if (m_paint == 3) {
            glDisable(GL_BLEND);
        }

        m_data.clear();
    }
}
