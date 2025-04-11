#include "TetraGame.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "screens/ScreenMain.hpp"

namespace tetrablocks::game {

    void TetraGame::init(){
        goMain();
        m_canvas.init();
        m_canvas.background(graphics::Color(0xFF202020));
    }

    void TetraGame::deinit(){
        m_canvas.deinit();
        m_screen->onClear();
    }

    void TetraGame::draw(){
        m_canvas.clear();
        m_screen->onDraw(m_canvas);
        m_canvas.draw();
    }

    void TetraGame::update(const float delta) const {
        m_screen->onUpdate(delta);
    }

    void TetraGame::onResize(const int w, const int h){
        m_canvas.resize({w,h});
        m_screen->onResize({w,h});
    }

    void TetraGame::onCursor(const float x, const float y) const {
        m_screen->onMouse({x,y});
    }

    void TetraGame::onKey(const int k, const int a, const int m) const {
        m_screen->onKey(k,a,m);
    }

    void TetraGame::goMain() {
       go<screens::ScreenMain>();
    }

    void TetraGame::goGame() {
        //TODO(Game screen navigation)
    }

    template<class T>
    void TetraGame::go() {
        if (m_screen) {
            m_screen->onClear();
        }
        m_screen = std::make_unique<T>(this);
        m_screen->onCreate(utils::Assets());
    }
}
