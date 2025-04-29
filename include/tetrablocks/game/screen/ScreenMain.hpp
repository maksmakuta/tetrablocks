#ifndef SCREENMAIN_HPP
#define SCREENMAIN_HPP

#include "tetrablocks/game/core/IScreen.hpp"
#include "tetrablocks/game/ui/Button.hpp"

namespace tetrablocks {

    class ScreenMain final : public IScreen {
    public:
        explicit ScreenMain(IController*);

        void onCreate() override;
        void onClear() override;

        void onDraw(Renderer &r) override;
        void onUpdate(float dt) override;

        void onResize(int w, int h) override;
        void onKey(int k, int a, int m) override;
        void onCursor(float x, float y) override;
    private:
        glm::vec2 m_view{0};
        glm::vec2 m_title{0};

        Button m_play;
        Button m_exit;
    };

}

#endif //SCREENMAIN_HPP
