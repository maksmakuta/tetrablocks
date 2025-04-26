#include "tetrablocks/game/Game.hpp"

#include <format>

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/model/Block.hpp"

namespace tetrablocks {

    constexpr auto size = glm::vec2{64,64};
    constexpr auto color = 0xFF808080;
    constexpr auto speed = 300.f;

    Game::Game() : m_font(24), m_wall(getAsset("/textures/wall.png")) {
        m_wall.bind();
        m_wall.setWrap(TextureWrap::Repeat);
        m_wall.setMinFilter(TextureMinFilter::LinearLinear);
        m_wall.setMagFilter(TextureFilter::Linear);
        m_wall.genMipmaps();

        m_font.load(getAsset("/fonts/Constance.otf"));

        m_rects.emplace_back(random({0, 0},{800, 600}),random(), randColor());
    }

    Game::~Game() = default;

    void Game::onDraw() {
        m_renderer.beginFrame();
        onRender(m_renderer);
        m_renderer.endFrame();
    }

    void Game::onTick(const float dt) {
        for(auto & m_rect : m_rects){
            auto& item = m_rect;
            item.pos += item.vel * (speed * dt);
            if (item.pos.x < -size.x || item.pos.y < -size.y ||
                item.pos.x > view.x || item.pos.y > view.y) {
                m_rect = {random({0, 0}, view), random(), randColor()};
            }
        }
        afps += 1.0 / dt;
        afps /= 2.0;
        if (afps > 60.0) {
            for (int i = 0; i < 5;i++)
                m_rects.emplace_back(random({0, 0},view),random(), randColor());
        }
    }

    void Game::onResize(const int w, const int h) {
        view = {w,h};
        m_renderer.resize(w,h);
    }

    void Game::onKey(int k, int a, int m){

    }

    void Game::onCursor(float x, float y){
        m = {x,y};
    }

    void Game::onRender(Renderer &r) {
        r.clear(0xFF202020);
        for (auto& c : m_rects) {
            r.fill(c.color);
            r.rect(c.pos.x,c.pos.y,size.x,size.y);
        }
        r.fill(0xFFFF0000);
        r.text(m_font,std::format("Rects: {}",m_rects.size()),{0,32});
    }
}
