#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "game/base/IWidget.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::ui {

    class Button final : public base::IWidget{
    public:
        Button() = default;

        void onCreate(const utils::Assets &, const std::string& name);
        void onClear();
        void onDraw(graphics::Canvas &);
        void onUpdate(float delta);
    private:
        graphics::Texture m_image;
    };

}

#endif //BUTTON_HPP
