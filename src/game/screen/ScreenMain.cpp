#include "tetrablocks/game/screen/ScreenMain.hpp"

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/game/core/IDialog.hpp"
#include "tetrablocks/game/screen/ScreenGame.hpp"

namespace tetrablocks {

    ScreenMain::ScreenMain(IController *c) : IScreen(c), m_play(c), m_exit(c) {}

    void ScreenMain::onCreate(){
        m_play.onCreate("Play",[this] {
            controller()->to<ScreenGame>();
        },{32,16});
        m_exit.onCreate("Exit",[this] {
            controller()->exit();
        },{32,16});
    }

    void ScreenMain::onClear(){
        m_play.onClear();
        m_exit.onClear();
    }

    void ScreenMain::onDraw(Renderer &r) {
        r.clear(0xFF1D1D7C);

        r.fill(0xFFFFFFFF);
        r.text(controller()->getAssets().m_font_title,"TetraBlocks",m_title, Align::Center);

        m_play.onDraw(r);
        m_exit.onDraw(r);
    }

    void ScreenMain::onUpdate(float dt){}

    void ScreenMain::onResize(int w, int h) {
        m_view = {w,h};
        m_play.pos = m_view / 2.f - m_play.getSize() / 2.f;
        m_exit.pos = m_play.pos + glm::vec2{(m_play.getSize() - m_exit.getSize()).x / 2.f,m_exit.getSize().y + 32};
        m_title = m_view / glm::vec2{2,3};
    }

    void ScreenMain::onKey(const int k, const int a, const int m){
        m_play.onKey(k,a,m);
        m_exit.onKey(k,a,m);
    }

    void ScreenMain::onCursor(const float x, const float y){
        m_play.onCursor(x,y);
        m_exit.onCursor(x,y);
    }

}
