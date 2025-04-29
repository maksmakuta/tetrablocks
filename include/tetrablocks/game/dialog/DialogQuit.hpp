#ifndef DIALOGQUIT_HPP
#define DIALOGQUIT_HPP

#include "tetrablocks/game/core/IController.hpp"
#include "tetrablocks/game/core/IDialog.hpp"
#include "tetrablocks/game/ui/Button.hpp"

namespace tetrablocks {

    class DialogQuit final : public IDialog {
    public:
        explicit DialogQuit(IController *c);

        void onCreate() override;
        void onClear() override;
        void onDraw(Renderer &r) override;
        void onUpdate(float dt) override;
        void onResize(int x, int y, int w, int h) override;
        void onKey(int k, int a, int m) override;
        void onCursor(float x, float y) override;
    private:
        Button m_yes;
        Button m_no;
        glm::vec4 m_rect;
        glm::vec2 m_title;
    };

}

#endif //DIALOGQUIT_HPP
