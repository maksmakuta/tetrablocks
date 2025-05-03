#ifndef SCRENNGAME_HPP
#define SCRENNGAME_HPP

#include <memory>
#include <random>

#include "tetrablocks/game/core/IScreen.hpp"
#include "tetrablocks/game/ui/Button.hpp"
#include "tetrablocks/model/Board.hpp"
#include "tetrablocks/model/Shape.hpp"

namespace tetrablocks {

    struct ShapeItem {
        Shape item;
        glm::vec2 pos;
    };

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
        [[nodiscard]] uint getRandom() const;
        void draw(Renderer &r, ShapeItem& s, bool selected) const;
        void drawBoard(Renderer& r);
        void checkShapes();

        std::unique_ptr<std::mt19937_64> m_random;
        std::array<ShapeItem,3> m_shapes;
        Board m_board;
        Button m_pause;
        glm::vec2 m_pos_score{0};
        glm::vec2 m_pos_board{0};
        glm::vec2 m_insert{0};
        glm::vec2 m_cell{0};
        glm::vec2 m_mouse{0};
        glm::uint m_score{0};
        int m_selected{-1};
    };

}

#endif //SCRENNGAME_HPP
