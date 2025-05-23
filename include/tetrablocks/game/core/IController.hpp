#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

#include "tetrablocks/game/core/Assets.hpp"

namespace tetrablocks {

    class IDialog;
    class IScreen;

    class IController {
    public:
        virtual ~IController() = default;

        virtual void go(IScreen* screen) = 0;
        virtual void show(IDialog* dialog) = 0;
        virtual void hide() = 0;
        virtual void exit() = 0;
        virtual Assets getAssets() = 0;

        template <class T> void to() {
            go(new T(this));
        }
    };

}

#endif //ICONTROLLER_HPP
