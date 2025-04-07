#include "TetraGame.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "utils/Assets.hpp"
#include "graphics/gl/gl.h"

namespace tetrablocks::game {

    void TetraGame::init(){
        m_texter.init(utils::Assets(),"burner.ttf");
        glClearColor(0.25f, 0.34f, 0.39f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void TetraGame::clear(){
        m_texter.clear();
    }

    void TetraGame::draw(){
        glClear(GL_COLOR_BUFFER_BIT);
        m_texter.text("Hello,World",{m.x,m.y});
        m_texter.draw(m_proj);
    }

    void TetraGame::update(float delta){

    }

    void TetraGame::onResize(const int w, const int h){
        glViewport(0,0,w,h);
        m_proj = glm::ortho<float>(0,w,h,0);
    }

    void TetraGame::onCursor(float x, float y) {
        m = {x,y};
    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
