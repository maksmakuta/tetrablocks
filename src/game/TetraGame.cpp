#include "TetraGame.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace tetrablocks::game {

    void TetraGame::init(){
        m_canvas.init();
        m_canvas.background(graphics::Color(0xFF80FF80));
    }

    void TetraGame::clear(){
        m_canvas.clear();
    }

    void TetraGame::draw(){
        onCanvas(m_canvas);
        m_canvas.draw();
    }

    void TetraGame::update(const float delta){

    }

    void TetraGame::onCanvas(graphics::Canvas &canvas) {

    }

    void TetraGame::onResize(const int w, const int h){
        m_canvas.resize({w,h});
    }

    void TetraGame::onCursor(float x, float y) {

    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
