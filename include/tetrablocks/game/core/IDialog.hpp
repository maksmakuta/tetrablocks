#ifndef IDIALOG_HPP
#define IDIALOG_HPP

#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    class IDialog {
    public:
        explicit IDialog(IController* c) : m_controller(c){}
        virtual ~IDialog() = default;

        virtual void onCreate() = 0;
        virtual void onClear() = 0;
        virtual void onDraw(Renderer& r) = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onResize(int x, int y,int w, int h) = 0;
        virtual void onKey(int k, int a, int m) = 0;
        virtual void onCursor(float x, float y) = 0;

        [[nodiscard]] IController* controller() const {
            return m_controller;
        }

    private:
        IController* m_controller{nullptr};
    };

}

#endif //IDIALOG_HPP
