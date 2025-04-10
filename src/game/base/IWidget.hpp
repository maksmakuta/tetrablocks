#ifndef IWIDGET_HPP
#define IWIDGET_HPP

#include "graphics/Canvas.hpp"
#include "utils/Assets.hpp"

namespace tetrablocks::base {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual void onCreate(const utils::Assets&) = 0;
        virtual void onClear() = 0;
        virtual void onDraw(graphics::Canvas&) = 0;
        virtual void onUpdate(float delta) = 0;

        void setPos(const glm::vec2& p) {
            pos = p;
        }

        void setSize(const glm::vec2& s) {
            size = s;
        }

        [[nodiscard]] glm::vec2 getSize() const {
            return size;
        }

        [[nodiscard]] glm::vec2 getPos() const {
            return pos;
        }
    private:
        glm::vec2 pos{0},size{0};
    };

}

#endif //IWIDGET_HPP
