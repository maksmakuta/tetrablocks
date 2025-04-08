#include "ShapeRenderer.hpp"

#include "graphics/gl/gl.h"

namespace tetrablocks::render {

    void ShapeRenderer::init(const utils::Assets& assets){
        m_shader.fromFiles(
            assets.getShader("vector.vert"),
            assets.getShader("vector.frag")
        );

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(ShapeVertex), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(ShapeVertex), reinterpret_cast<void *>((offsetof(ShapeVertex, col))));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void ShapeRenderer::clear(){
        m_shader.clear();
        glDeleteVertexArrays(1,&m_VAO);
        glDeleteBuffers(1,&m_VBO);
    }

    void ShapeRenderer::fill(){
        m_fill = true;
    }

    void ShapeRenderer::stroke(){
        m_fill = false;
    }

    void ShapeRenderer::setColor(const uint hex){
        m_color = hex;
    }

    void ShapeRenderer::setThickness(const float value){
        m_width = value;
    }

    void ShapeRenderer::line(const glm::vec2& a,const glm::vec2& b){
        const auto thick = m_width / 2.f;
        const auto dir = glm::normalize(b - a);
        const auto norm = glm::vec2(-dir.y,dir.x) * thick;

        m_data.emplace_back(a - norm,m_color);
        m_data.emplace_back(a + norm,m_color);
        m_data.emplace_back(b - norm,m_color);

        m_data.emplace_back(a + norm,m_color);
        m_data.emplace_back(b - norm,m_color);
        m_data.emplace_back(b + norm,m_color);
    }

    void ShapeRenderer::triangle(const glm::vec2& a,const glm::vec2& b, const glm::vec2& c){
        m_data.emplace_back(a,m_color);
        m_data.emplace_back(b,m_color);
        m_data.emplace_back(c,m_color);
    }

    void ShapeRenderer::square(const glm::vec2& a, const float size){
        rect(a,glm::vec2{size});
    }

    void ShapeRenderer::rect(const glm::vec2& origin,const glm::vec2& size){
        for(const auto& dir : std::vector<glm::vec2>{
                    {0,0},{1,0},{1,1},
                    {0,0},{1,1},{0,1},
        }) {
            m_data.emplace_back(origin + dir * size,m_color);
        }
    }

    void ShapeRenderer::draw(const glm::mat4& proj) {
        glUseProgram(m_shader.handle());

        m_shader.setMat4("proj",proj);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(ShapeVertex) * m_data.size()), m_data.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_data.size()));
        glBindVertexArray(0);

        m_data.clear();
    }

}
