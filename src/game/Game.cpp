#include "tetrablocks/game/Game.hpp"

#include <algorithm>
#include <execution>
#include <random>

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/model/Block.hpp"

namespace tetrablocks {

    constexpr auto size = glm::vec2{64,64};
    constexpr auto color = 0xFF808080;
    constexpr auto speed = 300.f;

    glm::vec2 random(const glm::vec2& min = {0,0}, const glm::vec2& max = {1,1}) {
        std::random_device rd;
        std::uniform_real_distribution ux{min.x, max.x};
        std::uniform_real_distribution uy{min.y, max.y};
        return {ux(rd),uy(rd)};
    }

    glm::uint randColor() {
        std::random_device rd;
        std::uniform_int_distribution u{0,255};
        return (0xFF << 24) | (u(rd) << 16) | (u(rd) << 8) | u(rd);
    }

    Game::Game() : m_wall(getAsset("/textures/wall.png")) {
        m_wall.bind();
        m_wall.setWrap(TextureWrap::Repeat);
        m_wall.setMinFilter(TextureMinFilter::LinearLinear);
        m_wall.setMagFilter(TextureFilter::Linear);
        m_wall.genMipmaps();

        m_font.loadFont(getAsset("/fonts/Constance.otf"));

        m_rects.emplace_back(random({0, 0},{800, 600}),random(), randColor());
    }

    Game::~Game() = default;

    void Game::onDraw() {
        onRender(m_renderer);
    }

    void Game::onTick(const float dt) {
        for(auto& r : m_rects){
            if (r.pos.x + size.x >= view.x || r.pos.x < 0) {
                r.vel.x *= -1;
            }
            if (r.pos.y + size.y >= view.y || r.pos.y < 0) {
                r.vel.y *= -1;
            }

            r.pos += (r.vel * speed) * dt;
        }
    }

    void Game::onResize(const int w, const int h) {
        view = {w,h};
        m_renderer.resize(w,h);
        // pos = random({0,0},{w,h});
        // vel = random({0,0},{1,1});
    }

    void Game::onKey(int k, int a, int m){

    }

    void Game::onCursor(float x, float y){
        m = {x,y};
    }

    void Game::onRender(Renderer &r) {
        r.clear(0xFF000000);
        for (auto& c : m_rects) {
            r.drawRect(c.pos.x,c.pos.y,size.x,size.y,c.color);
        }
        r.drawText(m_font,"Hello",m);
    }
}
