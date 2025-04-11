#include "Canvas.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>

#include "gl/gl.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::graphics {

    void Canvas::init() {
        const auto assets = utils::Assets();
        m_shader.fromFiles(
            assets.getShader("canvas.vert"),
            assets.getShader("canvas.frag")
        );

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, tex)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, col)));
        glEnableVertexAttribArray(2);
    }

    void Canvas::deinit() {
        m_shader.deinit();
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Canvas::draw() {
        if (m_vertices.empty())
            return;

        if (m_type == 3) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glUseProgram(m_shader.handle());
        m_shader.setMat4("u_mat",m_matrix);
        m_shader.setInt("type",m_type);
        m_shader.setInt("u_image",m_texture_id);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(m_vertices.size() * sizeof(Vertex)), m_vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));

        m_vertices.clear();
        if (m_type == 3) {
            glDisable(GL_BLEND);
        }
    }

    void Canvas::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Canvas::background(const Color& c) {
        glClearColor(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha());
    }

    void Canvas::resize(const glm::vec2& size) {
        glViewport(0,0,static_cast<int>(size.x),static_cast<int>(size.y));
        m_matrix = glm::ortho(0.f,size.x,size.y,0.f);
    }

    void Canvas::fill(const Color& c) {
        if (!m_vertices.empty()) {
            draw();
        }
        m_type = 1;
        m_texture_id = -1;
        m_uv = glm::vec4{0};
        m_stroke = false;
        m_color = c.toVec3();
    }

    void Canvas::fill(const Texture& t, const glm::vec4& uv) {
        if (!m_vertices.empty()) {
            draw();
        }

        t.bind();
        m_type = 2;
        m_texture_id = 0;
        m_uv = uv;
        m_color = {0,0,0};
        m_stroke = false;
    }

    void Canvas::stroke(const Color& c, const float w) {
        if (!m_vertices.empty()) {
            draw();
        }
        m_type = 1;
        m_texture_id = -1;
        m_uv = glm::vec4{0};
        m_stroke = true;
        m_color = c.toVec3();
        m_thickness = w;
    }

    void Canvas::text(const Font& fnt, const Color& c) {
        m_font = fnt;
        m_color = c.toVec3();
    }

    void Canvas::line(const glm::vec2& a,const glm::vec2& b) {
        draw(Path({a,b}));
    }

    void Canvas::triangle(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c) {
        draw(Path({a,b,c}));
    }

    void Canvas::quad(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c,const glm::vec2& d) {
        draw(Path({a,b,c,d}));
    }

    void Canvas::rect(const glm::vec2& a,const glm::vec2& b) {
        quad(
            a,
            a + glm::vec2{b.x,0},
            a + b,
            a + glm::vec2{0,b.y}
        );
    }

    void Canvas::rect(const glm::vec2& a,const glm::vec2& b, float r) {
        rect(a,b);
    }

    void Canvas::circle(const glm::vec2& c, const float r) {
        arc(c,glm::vec2{r},glm::vec2{0.f,glm::two_pi<float>()});
    }

    void Canvas::ellipse(const glm::vec2& c,const glm::vec2& r) {
        arc(c,r,glm::vec2{0.f,glm::two_pi<float>()});
    }

    glm::vec2 unit(const float alpha) {
        return {cosf(alpha),sinf(alpha)};
    }

    void Canvas::arc(const glm::vec2& c,const glm::vec2& r, const glm::vec2& a) {
        Path temp;
        float t = a.x;
        while(t < a.y) {
            temp.lineTo(c + unit(t) * r);
            t += glm::radians(5.f);
            if (t > a.y) t = a.y;
        }
        draw(temp);
    }

    void Canvas::pie(const glm::vec2& c,const glm::vec2& r, const glm::vec2& a) {
        Path temp;
        temp.moveTo(c);
        float t = a.x;
        while(t < a.y) {
            temp.lineTo(c + unit(t) * r);
            t += glm::radians(5.f);
            if (t > a.y) t = a.y;
        }
        draw(temp);
    }

    glm::vec2 calcUV(const glm::vec2 pos,const glm::vec2 range_a, const glm::vec2 range_b,const glm::vec2 uv_a, const glm::vec2 uv_b) {
        const auto delta = range_b - range_a;
        return mix(uv_a,uv_b,(pos - range_a) / delta);
    }

    std::vector<Vertex> triangulate(const Path &path, const glm::vec3& col,const glm::vec2 uv_a, const glm::vec2 uv_b, const bool calc_uv) {
        std::vector<Vertex> data;
        glm::vec2 min{9999999}, max{-9999999};
        if (calc_uv) {
            for (auto i = 0; i < path.length();++i) {
                const auto item = path[i];
                if (item.x < min.x) {
                    min.x = item.x;
                }
                if (item.y < min.y) {
                    min.y = item.y;
                }
                if (item.x > max.x) {
                    max.x = item.x;
                }
                if (item.y > max.y) {
                    max.y = item.y;
                }
            }
        }

        const Vertex origin{path[0], calc_uv ? calcUV(path[0],min,max,uv_a,uv_b) :glm::vec2{0,0},col};

        for (auto i = 0; i + 1 < path.length();++i) {
            data.push_back(origin);
            data.push_back({path[i], calc_uv ? calcUV(path[i],min,max,uv_a,uv_b) :glm::vec2{0,0},col});
            data.push_back({path[i + 1], calc_uv ? calcUV(path[i+1],min,max,uv_a,uv_b) :glm::vec2{0,0},col});
        }

        return data;
    }

    void Canvas::draw(const Path &path) {
        std::vector<Vertex> data;
        if (m_stroke) {

        }else {
            data = triangulate(path,m_color,{m_uv.x,m_uv.y},{m_uv.z,m_uv.w}, m_texture_id >= 0);
        }
        m_vertices.insert(m_vertices.end(),data.begin(), data.end());
    }

    void Canvas::draw(const std::string& text, const glm::vec2& pos, Align align, uint size){
        if (!m_vertices.empty()) {
            draw();
        }
        const float scale = size == 0 ? 1.f : static_cast<float>(size) / static_cast<float>(m_font.getSize());

        m_font.getTexture().bind();
        m_texture_id = 0;
        m_type = 3;
        glm::vec2 p = pos;

        if (align == Align::Center) {
            p.x += (m_font.getWidth(text) * scale) / 2.f;
        }
        if (align == Align::End) {
            p.x += m_font.getWidth(text) * scale;
        }

        for (const auto& c : text) {
            if (const auto glyph = m_font[c]; glyph) {

                const auto x = p.x + static_cast<float>(glyph->offset.x) * scale;
                const auto y = p.y - static_cast<float>(glyph->offset.y) * scale;
                const auto w = static_cast<float>(glyph->size.x) * scale;
                const auto h = static_cast<float>(glyph->size.y) * scale;

                const auto vertices = std::vector<Vertex>{
                        { glm::vec2{x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y}, m_color},
                        { glm::vec2{x,     y    },   {glyph->uv_a.x,glyph->uv_a.y}, m_color},
                        { glm::vec2{x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y}, m_color},
                        { glm::vec2{x,     y + h},   {glyph->uv_a.x,glyph->uv_b.y}, m_color},
                        { glm::vec2{x + w, y    },   {glyph->uv_b.x,glyph->uv_a.y}, m_color},
                        { glm::vec2{x + w, y + h},   {glyph->uv_b.x,glyph->uv_b.y}, m_color}
                };

                m_vertices.insert(m_vertices.end(),vertices.begin(), vertices.end());
                p.x += static_cast<float>(glyph->advance) * scale;
            }
        }

    }

}
