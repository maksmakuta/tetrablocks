#include "tetrablocks/game/Game.hpp"

namespace tetrablocks {

    Game::Game() {

    }

    Game::~Game() {

    }

    void Game::onDraw(Renderer& r) {
        r.clear(0xFF202020);
        r.drawRect(m.x,m.y,200,200,0xFFFFFF00);
    }

    void Game::onTick(float dt) {

    }

    void Game::onResize(int w, int h){

    }

    void Game::onKey(int k, int a, int m){

    }

    void Game::onScroll(float dx, float dy){

    }

    void Game::onCursor(float x, float y){
        m = {x,y};
    }

}