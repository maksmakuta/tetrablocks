#ifndef TETRAGAME_HPP
#define TETRAGAME_HPP

#include "graphics/Canvas.hpp"

namespace tetrablocks::game {

    class TetraGame {
    public:
        TetraGame() = default;

        void init();
        void clear();
        void draw();
        void update(float delta);

        void onCanvas(graphics::Canvas& canvas);
        void onResize(int w, int h);
        void onCursor(float x, float y);
        void onKey(int k, int a, int m);
    private:
        graphics::Canvas m_canvas;
    };

}

#endif //TETRAGAME_HPP
