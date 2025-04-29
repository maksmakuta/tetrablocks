#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>

#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    using Callback = std::function<void()>;

    class Button {
    public:
        Button() = default;

        void onCreate(const std::string& text, const Callback&, const glm::vec2& padding);
        void onClear();
        void onDraw(Renderer&);
        void onKey(int k, int a, int m);
        void onCursor(float x, float y);

    private:
        Callback m_callback;
        std::string m_text;
        glm::vec2 m_size{0};
    };

}

#endif //BUTTON_HPP
