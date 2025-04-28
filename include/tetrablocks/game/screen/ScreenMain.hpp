#ifndef SCREENMAIN_HPP
#define SCREENMAIN_HPP

#include "tetrablocks/game/core/IScreen.hpp"

namespace tetrablocks {

    class ScreenMain final : public IScreen {
    public:
        explicit ScreenMain(IController*);
        void onCreate() override;
        void onClear() override;
        void onDraw(Renderer &r) override;
        void onUpdate(float dt) override;
        void onResize(int w, int h) override;

        void switchDialog();

        void onKey(int k, int a, int m) override;
        void onCursor(float x, float y) override;
    private:

    };

}

#endif //SCREENMAIN_HPP
