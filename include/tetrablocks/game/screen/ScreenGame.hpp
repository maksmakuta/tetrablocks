#ifndef SCRENNGAME_HPP
#define SCRENNGAME_HPP

#include <array>

#include "tetrablocks/game/core/IScreen.hpp"
#include "tetrablocks/model/Board.hpp"

namespace tetrablocks {

    class ScreenGame final : public IScreen {
    public:
        explicit ScreenGame(IController*);

        void onCreate() override;
        void onClear() override;

        void onDraw(Renderer &r) override;
        void onUpdate(float dt) override;

        void onResize(int w, int h) override;
        void onKey(int k, int a, int m) override;
        void onCursor(float x, float y) override;

    private:
        Board m_board;
        std::array<Shape, 3> m_shapes;
    };

}

#endif //SCRENNGAME_HPP
