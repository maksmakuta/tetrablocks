#ifndef ISCREEN_HPP
#define ISCREEN_HPP

#include "IGameController.hpp"
#include "graphics/Canvas.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::base {

    class IScreen {
    public:
        explicit IScreen(IGameController* c) :m_controller(c) {}
        virtual ~IScreen() = default;

        virtual void onCreate(const utils::Assets&) = 0;
        virtual void onClear() = 0;
        virtual void onDraw(graphics::Canvas&) = 0;
        virtual void onUpdate(float delta) = 0;
        virtual void onMouse(const glm::vec2& mouse) = 0;
        virtual void onResize(const glm::vec2& size) = 0;
        virtual void onKey(int k, int a, int m) = 0;

    private:
        IGameController* m_controller = nullptr;
    };

}


#endif //ISCREEN_HPP
