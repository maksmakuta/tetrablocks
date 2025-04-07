#include "TetraGame.hpp"

#include "utils/Assets.hpp"
#include "graphics/gl/gl.h"

#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace tetrablocks::game {

    namespace detail {

        void loadShaders(graphics::Shader& s,const utils::Assets& assets, const std::string& name) {
            s.fromFiles(
                assets.getShader(name + ".vert"),
                assets.getShader(name + ".frag")
            );
        }

    }

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 col;
    };

    void TetraGame::init(){
        const utils::Assets assets;
        detail::loadShaders(m_shader,assets,"text");
        m_font.load(assets.getFont("burner.ttf"));

        const auto vertices = std::vector<Vertex>{
            {{  0,  0},{0,0}},
            {{  0,500},{0,1}},
            {{500,500},{1,1}},

            {{  0,  0},{0,0}},
            {{500,500},{1,1}},
            {{500,  0},{1,0}},
        };

        const int size = static_cast<int>(sizeof(Vertex) * vertices.size());

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void TetraGame::clear(){
        m_shader.clear();
        m_font.clear();
    }

    void TetraGame::draw(){
        glClear(GL_COLOR_BUFFER_BIT);

        m_font.getTexture().bind();

        glUseProgram(m_shader.handle());

        m_shader.setMat4("proj",m_proj);
        m_shader.setInt("u_image",0);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void TetraGame::update(float delta){

    }

    void TetraGame::onResize(const int w, const int h){
        glViewport(0,0,w,h);
        m_proj = glm::ortho<float>(0,w,h,0);
    }

    void TetraGame::onCursor(float x, float y){

    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
