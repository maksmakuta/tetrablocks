#ifndef GAME_HPP
#define GAME_HPP

#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    class Game {
    public:
        Game();
        ~Game();

        void init();
        void clear();

        void onDraw();
        void onTick(float dt);
        void onResize(int w, int h);
        void onKey(int k, int a, int m);
        void onCursor(float x, float y);
    private:
        void onRender(Renderer& r);

        Renderer m_renderer;
        Font m_font;
        Texture m_test;
        glm::vec2 m{0};
        glm::vec2 view{800,600};
    };

}

#endif //GAME_HPP
