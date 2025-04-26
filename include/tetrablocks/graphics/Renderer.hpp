#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

#include "Font.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace tetrablocks {

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 tex;
    };

    enum class Align : uint8_t{
        Center,
        Start,
        End
    };

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void resize(int w,int h);
        void clear(const glm::uint& color = 0xFF000000);

        void drawText(const Font& fnt, const std::string& text, const glm::vec2& pos, const glm::uint& col = 0xFFFFFFFF, const Align& = Align::Start);
        void drawRect(float x,float y,float w,float h, const glm::uint& col);
        void drawImage(float x,float y,float w,float h, const Texture& tex, const glm::vec2& uv_a = {0,0}, const glm::vec2& uv_b = {1,1});
        void push();

    private:
        glm::mat4 m_matrix{1.f};
        std::vector<Vertex> m_vertices;
        Shader m_shader;
        glm::uint m_vao;
        glm::uint m_vbo;
        glm::uint m_color;
        int m_type;
    };

}

#endif //RENDERER_HPP
