#include "Canvas.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>

#include "gl/gl.h"

namespace tetrablocks::graphics {

    void Canvas::init() {
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

        glUseProgram(m_shader.handle());
    }

    void Canvas::clear() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Canvas::draw() {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));
    }

    void Canvas::background(const Color& c) {
        glClearColor(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha());
    }

    void Canvas::resize(const glm::vec2& size) {
        glViewport(0,0,static_cast<int>(size.x),static_cast<int>(size.y));
        matrix = glm::ortho(0.f,size.x,size.y,0.f);
        m_shader.setMat4("u_mat",matrix);
    }

    void Canvas::fill(const Color&) {
        if (!m_vertices.empty()) {
            draw();
        }
    }

    void Canvas::fill(const Texture&, const glm::vec4& uv) {
        if (!m_vertices.empty()) {
            draw();
        }
    }

    void Canvas::stroke(const Color&, float w) {
        if (!m_vertices.empty()) {
            draw();
        }
    }

    void Canvas::line(const glm::vec2& a,const glm::vec2& b) {
        Path temp;
        temp.moveTo(a);
        temp.lineTo(b);
        draw(temp);
    }

    void Canvas::triangle(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c) {
        Path temp;
        temp.moveTo(a);
        temp.lineTo(b);
        temp.lineTo(c);
        draw(temp);
    }

    void Canvas::quad(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c,const glm::vec2& d) {
        Path temp;
        temp.moveTo(a);
        temp.lineTo(b);
        temp.lineTo(c);
        temp.lineTo(d);
        draw(temp);
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
        while(t <= a.y) {
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
        while(t <= a.y) {
            temp.lineTo(c + unit(t) * r);
            t += glm::radians(5.f);
            if (t > a.y) t = a.y;
        }
        draw(temp);
    }

    void Canvas::draw(const Path &path) {

    }

    void Canvas::text(const Font& fnt,const std::string& text, const glm::vec2& pos, Align align) {
        if (!m_vertices.empty()) {
            draw();
        }

        draw();
    }

}
