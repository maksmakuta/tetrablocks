#ifndef DIALOGEND_HPP
#define DIALOGEND_HPP

#include "tetrablocks/game/core/IController.hpp"
#include "tetrablocks/game/core/IDialog.hpp"
#include "tetrablocks/game/ui/Button.hpp"

namespace tetrablocks {
    class DialogEnd final : public IDialog {
    public:
        explicit DialogEnd(const glm::uint& points,IController *c);

        void onCreate() override;
        void onClear() override;
        void onDraw(Renderer &r) override;
        void onUpdate(float dt) override;
        void onResize(int x, int y, int w, int h) override;
        void onKey(int k, int a, int m) override;
        void onCursor(float x, float y) override;

    private:
        Button m_restart;
        Button m_exit;
        glm::vec4 m_rect{0};
        glm::vec2 m_title{0};
        glm::uint m_score{0};
    };

}

#endif //DIALOGEND_HPP
