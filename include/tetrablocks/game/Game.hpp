#ifndef GAME_HPP
#define GAME_HPP

#include <list>

#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    struct Rect {
        glm::vec2 pos;
        glm::vec2 vel;
        glm::uint color;
    };

    class Game {
    public:
        Game();
        ~Game();

        void onDraw();
        void onTick(float dt);
        void onResize(int w, int h);
        void onKey(int k, int a, int m);
        void onCursor(float x, float y);
    private:
        void onRender(Renderer& r);

        Renderer m_renderer;
        Font m_font;
        Texture m_wall;
        glm::vec2 m{0};

        std::list<Rect> m_rects;
        glm::vec2 view{800,600};
        double afps{144.0};
    };

}

#endif //GAME_HPP
