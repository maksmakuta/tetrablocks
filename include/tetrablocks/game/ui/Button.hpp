#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>

#include "tetrablocks/game/core/Assets.hpp"
#include "tetrablocks/game/core/IController.hpp"
#include "tetrablocks/graphics/Renderer.hpp"

namespace tetrablocks {

    using Callback = std::function<void()>;

    class Button {
    public:
        explicit Button(IController*);

        void onCreate(const std::string& text, const Callback&, const glm::vec2& padding = {32,16});
        void onClear();
        void onDraw(Renderer&);
        void onKey(int k, int a, int m);
        void onCursor(float x, float y);

        [[nodiscard]] glm::vec2 getSize() const;

        glm::vec2 pos{0};

    private:

        [[nodiscard]] Assets getAssets() const;

        Callback m_callback;
        std::string m_text;
        glm::vec2 m_size{0};
        IController* m_controller{nullptr};
        float delta{0.f};
        bool isHover{false};
    };

}

#endif //BUTTON_HPP
