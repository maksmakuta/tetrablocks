#include "ScreenMain.hpp"

#include <format>

namespace tetrablocks::screens {

    ScreenMain::ScreenMain(base::IGameController* c) : IScreen(c){}

    void ScreenMain::onCreate(const utils::Assets& assets){
        m_play.setSize(glm::vec2{50});
        m_exit.setSize(glm::vec2{50});

        m_font.load(assets.getFont("burner.ttf"),32);

        m_logo.loadPNG(assets.getTexture("title.png"));
        m_logo.setWrap(graphics::TextureWrap::Repeat);
        m_logo.setMagFilter(graphics::TextureFilter::Nearest);
        m_logo.setMinFilter(graphics::TextureFilter::Linear);
        m_logo.genMipmaps();

        m_play.onCreate(assets,"ui/play.png");
        m_exit.onCreate(assets,"ui/exit.png");
    }

    void ScreenMain::onClear(){
        m_font.deinit();
    }

    void ScreenMain::onDraw(graphics::Canvas& c){
        c.fill(m_logo);
        c.rect(pos_logo,m_logo.getSize()*3u);

        m_play.onDraw(c);
        m_exit.onDraw(c);

        c.text(m_font,graphics::Color(0xFFFFFFFF));
        c.draw("Maks Makuta (C)", pos_author,graphics::Align::Start,20);
    }

    void ScreenMain::onUpdate(float delta){

    }

    void ScreenMain::onMouse(const glm::vec2 &mouse){

    }

    void ScreenMain::onResize(const glm::vec2 &size){
        if (m_logo.getHandle() != 0) {
            const auto logo_size = m_logo.getSize() * 3u;
            pos_logo = glm::vec2(size.x / 2.f - logo_size.x / 2.f, size.y / 3.f - logo_size.y / 2.f);
        }
        pos_author = {5,size.y-5};

        m_play.setPos(size / 2.f - m_play.getSize() / 2.f);
    }

    void ScreenMain::onKey(const int k, const int a, const int m){

    }


}

