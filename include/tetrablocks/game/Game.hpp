#ifndef GAME_HPP
#define GAME_HPP

#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    class Game {
    public:
        Game();
        ~Game();

        void onDraw(Renderer&);
        void onTick(float dt);

        void onResize(int w, int h);
        void onKey(int k, int a, int m);
        void onScroll(float dx, float dy);
        void onCursor(float x, float y);
    };

}

#endif //GAME_HPP
