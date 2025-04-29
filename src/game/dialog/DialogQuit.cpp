#include "tetrablocks/game/dialog/DialogQuit.hpp"

#include <GLFW/glfw3.h>

#include "tetrablocks/Constants.hpp"

namespace tetrablocks {

    DialogQuit::DialogQuit(IController *c) : IDialog(c), m_yes(c), m_no(c), m_rect(0), m_title(0){}

    void DialogQuit::onCreate(){
        m_yes.onCreate("Yes",[this]{
            controller()->exit();
        });

        m_no.onCreate("No",[this]{
            controller()->hide();
        });
    }

    void DialogQuit::onClear(){
        m_yes.onClear();
        m_no.onClear();
    }

    void DialogQuit::onDraw(Renderer &r){
        r.fill(COLOR_DIALOG_BG);
        r.rect(m_rect.x,m_rect.y,m_rect.z,m_rect.w);

        r.fill(COLOR_TEXT);
        r.text(controller()->getAssets().m_font, "Are you sure?", m_title,Align::Center);

        m_yes.onDraw(r);
        m_no.onDraw(r);
    }

    void DialogQuit::onUpdate(float dt){}

    void DialogQuit::onResize(int x, int y, int w, int h) {
        m_rect = {x,y,w,h};
        m_title = glm::vec2{x,y} + glm::vec2{w,h} / 2.f;

        const auto box = glm::vec2{w/2,h/3};

        m_yes.pos = glm::vec2{x      ,y + h * 0.67} + (box / 2.f - m_yes.getSize() / 2.f);
        m_no.pos  = glm::vec2{x + w/2,y + h * 0.67} + (box / 2.f - m_no.getSize()  / 2.f);
    }

    void DialogQuit::onKey(const int k, const int a, const int m){
        if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
            controller()->hide();
        }
        m_yes.onKey(k,a,m);
        m_no.onKey(k,a,m);
    }

    void DialogQuit::onCursor(const float x, const float y){
        m_yes.onCursor(x,y);
        m_no.onCursor(x,y);
    }

}
