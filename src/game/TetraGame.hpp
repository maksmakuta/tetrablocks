#ifndef TETRAGAME_HPP
#define TETRAGAME_HPP

#include "graphics/Canvas.hpp"

namespace tetrablocks::game {

    class TetraGame {
    public:
        TetraGame() = default;

        void init();
        void deinit();
        void draw();
        void update(float delta);

        void onCanvas(graphics::Canvas& c);
        void onResize(int w, int h);
        void onCursor(float x, float y);
        void onKey(int k, int a, int m);
    private:
        graphics::Canvas m_canvas;
        graphics::Font m_font;
        glm::vec2 mouse{0,0};
    };

}

#endif //TETRAGAME_HPP
