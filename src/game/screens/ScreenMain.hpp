#ifndef SCREENMAIN_HPP
#define SCREENMAIN_HPP

#include "game/base/IScreen.hpp"
#include "game/ui/Button.hpp"

namespace tetrablocks::screens {

    class ScreenMain final : public base::IScreen {
    public:
        explicit ScreenMain(base::IGameController*);

        void onCreate(const utils::Assets&) override;
        void onClear() override;
        void onDraw(graphics::Canvas &) override;
        void onUpdate(float delta) override;
        void onMouse(const glm::vec2 &mouse) override;
        void onResize(const glm::vec2 &size) override;
        void onKey(int k, int a, int m) override;
    private:
        graphics::Font m_font;
        graphics::Texture m_logo;

        ui::Button m_play;

        glm::vec2 pos_logo{0};
        glm::vec2 pos_author{0};
    };

}

#endif //SCREENMAIN_HPP
