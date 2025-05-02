#include "tetrablocks/game/dialog/DialogEnd.hpp"

#include <format>

#include "tetrablocks/Constants.hpp"
#include "tetrablocks/game/screen/ScreenGame.hpp"
#include "tetrablocks/game/screen/ScreenMain.hpp"

namespace tetrablocks {

    DialogEnd::DialogEnd(const glm::uint& points,IController *c) : IDialog(c), m_restart(c), m_exit(c), m_score(points){}

    void DialogEnd::onCreate(){
        m_restart.onCreate("Restart",[this] {
            controller()->to<ScreenGame>();
        });
        m_exit.onCreate("To Main",[this] {
            controller()->to<ScreenMain>();
        });
    }

    void DialogEnd::onClear(){
        m_restart.onClear();
        m_exit.onClear();
    }

    void DialogEnd::onDraw(Renderer &r){
        r.fill(COLOR_DIALOG_BG);
        r.rect(m_rect.x,m_rect.y,m_rect.z,m_rect.w);

        const glm::vec2 center = {m_rect.x + m_rect.z / 2,m_rect.y + m_rect.w / 2};

        r.fill(COLOR_TEXT);
        r.text(controller()->getAssets().m_font,"GAME IS OVER",m_title,Align::Center);
        r.text(controller()->getAssets().m_font,std::format("Your score : {}",m_score),center,Align::Center);

        m_restart.onDraw(r);
        m_exit.onDraw(r);
    }

    void DialogEnd::onUpdate(float dt){}

    void DialogEnd::onResize(int x, int y, int w, int h){
        m_rect = {x,y,w,h};
        m_title = {x + w/2,y + h * 0.33};
        m_restart.pos = glm::vec2{x + w * 0.25,y + h * 0.66} - m_restart.getSize() / 2.f;
        m_exit.pos = glm::vec2{x + w * 0.75,y + h * 0.66} - m_exit.getSize() / 2.f;
    }

    void DialogEnd::onKey(const int k, const int a, const int m){
        m_restart.onKey(k,a,m);
        m_exit.onKey(k,a,m);
    }

    void DialogEnd::onCursor(const float x, const float y){
        m_restart.onCursor(x,y);
        m_exit.onCursor(x,y);
    }

}
