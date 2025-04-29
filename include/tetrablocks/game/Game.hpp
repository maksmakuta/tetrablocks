#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "core/Assets.hpp"
#include "tetrablocks/game/core/IScreen.hpp"
#include "tetrablocks/game/core/IDialog.hpp"
#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    class Game final : public IController{
    public:
        Game();
        ~Game() override;

        void init();
        void clear();

        void onDraw();
        void onTick(float dt);
        void onResize(int w, int h);
        void onKey(int k, int a, int m);
        void onCursor(float x, float y);

        void go(IScreen *screen) override;
        void show(IDialog *dialog) override;
        Assets getAssets() override;
        void hide() override;
        void exit() override;

    private:
        Renderer m_renderer;
        Assets m_assets;
        std::unique_ptr<IScreen> m_screen;
        std::unique_ptr<IDialog> m_dialog;
        glm::ivec2 m_view{0};
    };

}

#endif //GAME_HPP
