#include "tetrablocks/game/dialog/DialogPause.hpp"

#include <GLFW/glfw3.h>

#include "tetrablocks/game/screen/ScreenGame.hpp"
#include "tetrablocks/game/screen/ScreenMain.hpp"

namespace tetrablocks {

    DialogPause::DialogPause(IController *c) : IDialog(c), m_restart(c), m_exit(c), m_play(c){}

    void DialogPause::onCreate(){
        m_restart.onCreate("Restart",[this] {
            controller()->to<ScreenGame>();
        });
        m_play.onCreate("Play",[this]{
            controller()->hide();
        });
        m_exit.onCreate("Exit",[this]{
            controller()->to<ScreenMain>();
        });
    }

    void DialogPause::onClear(){
        m_restart.onClear();
        m_play.onClear();
        m_exit.onClear();
    }

    void DialogPause::onDraw(Renderer &r){
        r.fill(COLOR_DIALOG_BG);
        r.rect(m_rect.x,m_rect.y,m_rect.z,m_rect.w);

        r.fill(COLOR_TEXT);
        r.text(controller()->getAssets().m_font,"Pause Menu",m_title,Align::Center);

        m_restart.onDraw(r);
        m_play.onDraw(r);
        m_exit.onDraw(r);
    }

    void DialogPause::onUpdate(float dt){}

    void DialogPause::onResize(int x, int y, int w, int h){
        m_rect = {x,y,w,h};
        m_title = {x + w / 2, y + h * 0.25};

        m_restart.pos = glm::vec2{x + w / 2,y + h / 2} - m_restart.getSize() / 2.f;

        m_play.pos = glm::vec2{x + w * 0.25,y + h * 0.75} - m_play.getSize() / 2.f;;
        m_exit.pos = glm::vec2{x + w * 0.75,y + h  * 0.75} - m_exit.getSize() / 2.f;;
    }

    void DialogPause::onKey(const int k, const int a, const int m){
        if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
            controller()->hide();
        }
        m_restart.onKey(k,a,m);
        m_play.onKey(k,a,m);
        m_exit.onKey(k,a,m);
    }

    void DialogPause::onCursor(const float x, const float y){
        m_restart.onCursor(x,y);
        m_play.onCursor(x,y);
        m_exit.onCursor(x,y);
    }

}
