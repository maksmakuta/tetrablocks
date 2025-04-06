#include "TetraGame.hpp"

#include <vector>

#include "utils/Assets.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "graphics/gl/gl.h"

namespace tetrablocks::game {

    struct Vertex {
        glm::vec2 pos;
        glm::vec3 col;
    };

    void TetraGame::init(){
        const utils::Assets assets;
        m_shader.fromFiles(assets.getShader("triangle.vert"),assets.getShader("triangle.frag"));

        const auto vertices = std::vector<Vertex>{
            {{-0.5,-0.5},{1,0,0}},
            {{ 0.5,-0.5},{0,1,0}},
            {{ 0.0, 0.5},{0,0,1}}
        };

        const int size = static_cast<int>(sizeof(Vertex) * vertices.size());

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void TetraGame::clear(){
        m_shader.clear();
    }

    void TetraGame::draw(){
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shader.handle());
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void TetraGame::update(float delta){

    }

    void TetraGame::onResize(const int w, const int h){
        glViewport(0,0,w,h);
        m_proj = glm::ortho(0,w,h,0);
    }

    void TetraGame::onCursor(float x, float y){

    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
