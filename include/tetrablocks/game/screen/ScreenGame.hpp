#ifndef SCRENNGAME_HPP
#define SCRENNGAME_HPP

#include "tetrablocks/game/core/IScreen.hpp"
#include "tetrablocks/game/ui/Button.hpp"
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
        void drawBoard(Renderer& r, const glm::vec4& rect);
        void drawShapes(Renderer& r, const glm::vec4& rect);
        void drawHeader(Renderer& r, const glm::vec4& rect);

        Button m_pause;
        Board m_board;
        std::vector<Shape> m_shapes;
        glm::vec2 m_view{0};
        glm::vec2 m_mouse{0};
        glm::vec4 m_rect_board{0};
        glm::vec4 m_rect_header{0};
        glm::vec4 m_rect_shapes{0};
        glm::uint m_score{0};
    };

}

#endif //SCRENNGAME_HPP
