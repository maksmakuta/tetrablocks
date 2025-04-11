#include "ScreenMain.hpp"

#include <format>

namespace tetrablocks::screens {

    ScreenMain::ScreenMain(base::IGameController* c) : IScreen(c){}

    void ScreenMain::onCreate(const utils::Assets& assets){
        m_font.load(assets.getFont("burner.ttf"),32);
        size = m_font.getSize();
    }

    void ScreenMain::onClear(){
        m_font.deinit();
    }

    void ScreenMain::onDraw(graphics::Canvas& c){
        c.text(m_font,graphics::Color(0xFFFFFFFF));
        c.draw("Hello, World|",m,graphics::Align::Start,size);
    }

    void ScreenMain::onUpdate(float delta){

    }

    void ScreenMain::onMouse(const glm::vec2 &mouse){

    }

    void ScreenMain::onResize(const glm::vec2 &size){

    }

    void ScreenMain::onKey(const int k, const int a, const int m){

    }


}

