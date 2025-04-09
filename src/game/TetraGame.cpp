#include "TetraGame.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "utils/Assets.hpp"

namespace tetrablocks::game {

    void TetraGame::init(){
        m_font.load(utils::Assets().getFont("burner.ttf"));
        m_canvas.init();
        m_canvas.background(graphics::Color(0xFF202020));
    }

    void TetraGame::clear(){
        m_canvas.clear();
        m_font.clear();
    }

    void TetraGame::draw(){
        m_canvas.blank();
        onCanvas(m_canvas);
        m_canvas.draw();
    }

    void TetraGame::update(const float delta){

    }

    void TetraGame::onCanvas(graphics::Canvas& c) {
        c.fill(m_font.getTexture());
        c.rect({300,350},{512,512});

        c.fill(graphics::Color(0xFF00FFFF));
        c.circle({300,300},50);
        c.rect({100,350},{150,175});
        c.triangle({10,10},{100,100},{10,200});


        c.fill(graphics::Color(0xFFFFFFFF));
        c.text(m_font,"Just text",mouse);
    }

    void TetraGame::onResize(const int w, const int h){
        m_canvas.resize({w,h});
    }

    void TetraGame::onCursor(float x, float y) {
        mouse = {x,y};
    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
