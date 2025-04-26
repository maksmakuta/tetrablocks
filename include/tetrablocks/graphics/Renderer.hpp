#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

#include "Font.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace tetrablocks {

    using HexColor = glm::uint;
    using OrthoMatrix = std::pair<glm::vec3,glm::vec3>;

    struct Vertex {
        glm::uint pos_type;
        glm::uint col;
        glm::uint tex;

        Vertex(int type, const glm::vec2& pos, const HexColor& color, const glm::vec2& uv);
    };

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void resize(int w,int h);
        void clear(const HexColor& color = 0xFF000000);

        void beginFrame();
        void endFrame();

        void fill(const HexColor& col = 0xFFFFFFFF);
        void image(const Texture& tex, const glm::vec2& uv_a = {0,0}, const glm::vec2& uv_b = {1,1});

        void rect(float x,float y,float w,float h);
        void text(const Font& fnt, const std::string& text, const glm::vec2& pos, const Align& = Align::Start);

    private:
        std::vector<Vertex> m_data;
        OrthoMatrix m_matrix;
        Shader m_shader;
        glm::uint m_vao;
        glm::uint m_vbo;
        int m_paint;
    };

}

#endif //RENDERER_HPP
