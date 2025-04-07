#ifndef TETRAGAME_HPP
#define TETRAGAME_HPP

#include <glm/mat4x4.hpp>

#include "graphics/Font.hpp"
#include "graphics/Shader.hpp"

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
        glm::uint m_VAO{0}, m_VBO{0};
        glm::mat4 m_proj{1.f};
        graphics::Shader m_shader;
        graphics::Font m_font;
    };

}

#endif //TETRAGAME_HPP
