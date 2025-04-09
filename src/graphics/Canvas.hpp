#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include "Color.hpp"
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
        void clear();
        void draw();

        void resize(const glm::vec2&);

        //drawing settings
        void fill(const Color&);
        void fill(const Texture&, const glm::vec4& uv = {0,0,1,1});
        void stroke(const Color&, float w = 5.f);

        void line(const glm::vec2& a,const glm::vec2& b);
        void triangle(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c);
        void quad(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c,const glm::vec2& d);
        void rect(const glm::vec2& a,const glm::vec2& b);
        void rect(const glm::vec2& a,const glm::vec2& b, float r);
        void circle(const glm::vec2& c, float r);
        void ellipse(const glm::vec2& c,const glm::vec2& r);
        void arc(const glm::vec2& c, float r);
        void pie(const glm::vec2& c,const glm::vec2& r);

        /**
         * text function don't inherit drawing settings
         * @param text : std::string - text to draw
         * @param pos : glm::vec2 - text position
         * @param align : Align - text horizontal alignment
         */
        void text(const std::string& text, const glm::vec2& pos, Align align = Align::Start);
    };

}

#endif //CANVAS_HPP
