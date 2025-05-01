#include "tetrablocks/game/ui/Button.hpp"

#include <GLFW/glfw3.h>

#include "tetrablocks/Constants.hpp"
#include "tetrablocks/Utils.hpp"

namespace tetrablocks {

    Button::Button(IController *c) : m_controller(c){}

    void Button::onCreate(const std::string& text, const Callback& callback, const glm::vec2& padding) {
        m_size = padding + glm::vec2{getAssets().m_font.width(text),getAssets().m_font.getSize()};
        m_text = text;
        m_callback = callback;
        delta = static_cast<float>(getAssets().m_font.height(m_text) - getAssets().m_font.getSize()) * 2.f;
    }

    void Button::onClear() {
        m_callback = nullptr;
    }

    void Button::onDraw(Renderer& r) {
        r.fill(isHover ? COLOR_BTN_BG_HOVER : COLOR_BTN_TEXT);
        r.rect(pos.x,pos.y,m_size.x,m_size.y);
        r.fill(COLOR_BTN_BG);
        r.rect(pos.x + BUTTON_BORDER,pos.y + BUTTON_BORDER,m_size.x - 2 * BUTTON_BORDER,m_size.y - 2 * BUTTON_BORDER);
        r.fill(isHover ? COLOR_BTN_BG_HOVER : COLOR_BTN_TEXT);
        r.text(getAssets().m_font,m_text,pos + m_size / 2.f - glm::vec2{0,delta},Align::Center);
    }

    void Button::onKey(const int k, const int a, int) {
        if (k == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_PRESS && isHover && m_callback) {
            m_callback();
        }
    }

    void Button::onCursor(float x, float y) {
        isHover = inRect({pos,m_size},{x,y});
    }

    glm::vec2 Button::getSize() const {
        return m_size;
    }

    Assets Button::getAssets() const {
        return m_controller->getAssets();
    }
}
