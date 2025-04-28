#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

namespace tetrablocks {

    class IDialog;
    class IScreen;

    class IController {
    public:
        virtual ~IController() = default;

        virtual void go(IScreen* screen) = 0;
        virtual void show(IDialog* dialog) = 0;
        virtual void hide() = 0;
    };

}

#endif //ICONTROLLER_HPP
