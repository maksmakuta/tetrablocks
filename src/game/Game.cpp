#include "tetrablocks/game/Game.hpp"

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/model/Block.hpp"

namespace tetrablocks {

    Game::Game() : m_wall(getAsset("/textures/wall.png")){
        m_wall.bind();
        m_wall.setWrap(TextureWrap::Repeat);
        m_wall.setMinFilter(TextureFilter::Linear);
        m_wall.setMagFilter(TextureFilter::Linear);
        m_wall.genMipmaps();
    }

    Game::~Game() = default;

    void Game::onDraw() {
        onRender(m_renderer);
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

    void Game::onRender(Renderer &r) {
        r.clear(getColor(Block::Cyan));

        r.drawRect(0,0,256,256,getColor(Block::Orange));
        r.drawImage(0,256,256,256,m_wall);

    }
}
