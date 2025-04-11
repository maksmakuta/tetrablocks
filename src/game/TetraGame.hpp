#ifndef TETRAGAME_HPP
#define TETRAGAME_HPP

#include <memory>

#include "base/IGameController.hpp"
#include "base/IScreen.hpp"
#include "graphics/Canvas.hpp"

namespace tetrablocks::game {

    class TetraGame final : public base::IGameController{
    public:
        TetraGame() = default;

        void init();
        void deinit();
        void draw();
        void update(float delta) const;

        void onResize(int w, int h);
        void onCursor(float x, float y) const;
        void onKey(int k, int a, int m) const;

        void goMain() override;
        void goGame() override;

        template<class T>
        void go();

    private:
        graphics::Canvas m_canvas;
        std::unique_ptr<base::IScreen> m_screen;
    };

}

#endif //TETRAGAME_HPP
