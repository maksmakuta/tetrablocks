#ifndef IGAMECONTROLLER_HPP
#define IGAMECONTROLLER_HPP

namespace tetrablocks::base {

    class IGameController {
    public:
        virtual ~IGameController() = default;

        virtual void goMain() = 0;
        virtual void goGame() = 0;
    };

}

#endif //IGAMECONTROLLER_HPP
