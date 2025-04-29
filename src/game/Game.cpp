#include "tetrablocks/game/Game.hpp"

#include <string>

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/game/screen/ScreenMain.hpp"

namespace tetrablocks {

    constexpr auto DIALOG_SIZE = glm::vec2{0.75,0.5};

    Game::Game() : m_screen(std::make_unique<ScreenMain>(this)){}

    Game::~Game() = default;

    void Game::init() {

        m_assets = {};
        m_assets.init(getAsset("/fonts/Constance.otf"));
        m_screen->onCreate();
    }

    void Game::clear() {
        m_screen->onClear();
        if (m_dialog) {
            m_dialog->onClear();
        }

        m_assets.m_font.clear();
        m_assets.m_font_title.clear();
    }

    void Game::onDraw() {
        m_renderer.beginFrame();
        m_screen->onDraw(m_renderer);
        if (m_dialog) {
            m_dialog->onDraw(m_renderer);
        }
        m_renderer.endFrame();
    }

    void Game::onTick(const float dt) {
        if (m_dialog) {
            m_dialog->onUpdate(dt);
        }else{
            m_screen->onUpdate(dt);
        }
    }

    void Game::onResize(const int w, const int h) {
        m_view = {w,h};
        m_renderer.resize(w,h);
        m_screen->onResize(w,h);
        if (m_dialog) {
            const auto size = glm::ivec2(glm::vec2(m_view) * DIALOG_SIZE);
            const auto pos = m_view / 2 - size / 2;
            m_dialog->onResize(pos.x,pos.y,size.x,size.y);
        }
    }

    void Game::onKey(const int k, const int a, const int m) {
        if (m_dialog) {
            m_dialog->onKey(k,a,m);
        }else{
            m_screen->onKey(k,a,m);
        }
    }

    void Game::onCursor(const float x, const float y) {
        if (m_dialog) {
            m_dialog->onCursor(x,y);
        }else{
            m_screen->onCursor(x,y);
        }
    }

    void Game::go(IScreen *screen) {
        m_screen->onClear();
        m_screen.reset(screen);
        if (m_screen){
            m_screen->onCreate();
            m_screen->onResize(m_view.x,m_view.y);
        }
    }

    void Game::show(IDialog *dialog){
        if (m_dialog) {
            m_dialog->onClear();
        }

        m_dialog.reset(dialog);

        if (m_dialog){
            m_dialog->onCreate();
            const auto size = glm::ivec2(glm::vec2(m_view) * DIALOG_SIZE);
            const auto pos = m_view / 2 - size / 2;
            m_dialog->onResize(pos.x,pos.y,size.x,size.y);
        }
    }

    Assets Game::getAssets() {
        return m_assets;
    }

    void Game::hide() {
        show(nullptr);
    }

    void Game::exit() {
        std::exit(0);
    }
}

