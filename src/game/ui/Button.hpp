#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "game/base/IWidget.hpp"

namespace tetrablocks::ui {

    class Button : public base::IWidget{
    public:
        Button();

        void onCreate(const utils::Assets &) override;
        void onClear() override;
        void onDraw(graphics::Canvas &) override;
        void onUpdate(float delta) override;
    };

}

#endif //BUTTON_HPP
