#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/vec2.hpp>

namespace tetrablocks {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        //low-level rendering
        void drawTile();
        void drawText();
        void drawRect();
        void drawImage();

    private:
        glm::uint m_program;
        glm::uint m_vao, m_vbo;
    };

}

#endif //RENDERER_HPP
