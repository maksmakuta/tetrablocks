#include "tetrablocks/game/Game.hpp"

#include <format>

#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Game::Game(){
        m_font.load(getAsset("/fonts/Constance.otf"));
    }

    Game::~Game() {
        m_font.clear();
    }

    void Game::init() {

    }

    void Game::clear() {

    }

    void Game::onDraw() {
        m_renderer.beginFrame();
        onRender(m_renderer);
        m_renderer.endFrame();
    }

    void Game::onTick(const float dt) {

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

        r.image(m_font.getTexture());
        r.rect(0,0,512,512);

        r.fill(0xFF00FF00);
        r.text(m_font,"Hello, World",m);
    }
}
