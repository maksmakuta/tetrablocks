#include "tetrablocks/game/Game.hpp"

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/model/Block.hpp"

namespace tetrablocks {

    Game::Game() : m_font(getAsset("/fonts/Constance.otf"),24), m_image(getAsset("/textures/wall.png")){

    }

    Game::~Game() = default;

    void Game::onDraw() {
        auto& r = this->m_renderer;
        r.clear(0xFF202020);

        r.drawRect(0,0,50,50,getColor(Block::Purple));

        const auto s = m_font.getTexture().getSize();
        r.drawImage(m.x,m.y,s.x,s.y,m_image);

        r.drawText(m_font,"Just text",{0,m_font.getSize()},getColor(Block::Green));

    }

    void Game::onTick(float dt) {

    }

    void Game::onResize(const int w, const int h){
        m_renderer.resize(w,h);
    }

    void Game::onKey(int k, int a, int m){

    }

    void Game::onCursor(float x, float y){
        m = {x,y};
    }

}
