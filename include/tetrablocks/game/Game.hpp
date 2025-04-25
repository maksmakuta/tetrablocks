#ifndef GAME_HPP
#define GAME_HPP

#include "tetrablocks/graphics/Renderer.hpp"
#include "tetrablocks/graphics/Texture.hpp"

namespace tetrablocks {

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
        Texture m_wall;
        glm::vec2 m{0};
    };

}

#endif //GAME_HPP
