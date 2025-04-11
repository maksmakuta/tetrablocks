#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include "Color.hpp"
#include "Font.hpp"
#include "Path.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace tetrablocks::graphics {

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 tex;
        glm::vec3 col;
    };

    enum class Align : uint8_t{
        Center,
        Start,
        End
    };

    class Canvas {
    public:
        Canvas() = default;

        void init();
        void deinit();
        void draw();

        void clear();
        void background(const Color&);
        void resize(const glm::vec2&);

        //drawing settings
        void fill(const Color&);
        void fill(const Texture&, const glm::vec4& uv = {0,0,1,1});
        void stroke(const Color&, float w = 5.f);
        void text(const Font& fnt,const Color&);

        void line(const glm::vec2& a,const glm::vec2& b);
        void triangle(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c);
        void quad(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c,const glm::vec2& d);
        void rect(const glm::vec2& a,const glm::vec2& b);
        void rect(const glm::vec2& a,const glm::vec2& b, float r);
        void circle(const glm::vec2& c, float r);
        void ellipse(const glm::vec2& c,const glm::vec2& r);
        void arc(const glm::vec2& c,const glm::vec2& r, const glm::vec2& a);
        void pie(const glm::vec2& c,const glm::vec2& r, const glm::vec2& a);

        void draw(const Path& path);

        /**
         * text function don't inherit drawing settings
         * @param text : std::string - text to draw
         * @param pos : glm::vec2 - text position
         * @param align : Align - text horizontal alignment
         */
        void draw(const std::string& text, const glm::vec2& pos, Align align = Align::Start, uint size = 0);
    private:
        std::vector<Vertex> m_vertices;
        Font m_font;
        glm::mat4 m_matrix{1.f};
        glm::vec4 m_uv{0,0,1,1};
        glm::vec3 m_color{1,1,1};
        Shader m_shader;
        float m_thickness{0.f};
        int m_texture_id{-1};
        uint VBO{0}, VAO{0};
        uint8_t m_type = 1;
        bool m_stroke{false};
    };

}

#endif //CANVAS_HPP
