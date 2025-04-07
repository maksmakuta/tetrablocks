#ifndef TETRAGAME_HPP
#define TETRAGAME_HPP

#include <glm/mat4x4.hpp>

#include "graphics/Font.hpp"
#include "graphics/Shader.hpp"
#include "render/TextRenderer.hpp"

namespace tetrablocks::game {

    class TetraGame {
    public:
        TetraGame() = default;

        void init();
        void clear();
        void draw();
        void update(float delta);

        void onResize(int w, int h);
        void onCursor(float x, float y);
        void onKey(int k, int a, int m);
    private:
        render::TextRenderer m_texter;
        glm::mat4 m_proj{1.f};
        glm::vec2 m{0};
        float fps{0.f};
    };

}

#endif //TETRAGAME_HPP
