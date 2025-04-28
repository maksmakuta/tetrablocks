#include "tetrablocks/game/screen/ScreenMain.hpp"

#include <GLFW/glfw3.h>

#include "tetrablocks/game/core/IDialog.hpp"

namespace tetrablocks {

    class TestDialog : public IDialog {
    public:
        explicit TestDialog(IController* c) : IDialog(c){}
        void onCreate() override {}
        void onClear() override{}
        void onDraw(Renderer &r) override {
            r.fill(0xFF00FF00);
            r.rect(m_rect.x,m_rect.y,m_rect.z,m_rect.w);
        }
        void onResize(int x, int y, int w, int h) override {
            m_rect = {x,y,w,h};
        }
        void onUpdate(float dt) override{}
        void onKey(int k, int a, int m) override {
            if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
                controller()->hide();
            }
        }
        void onCursor(float x, float y) override{}
    private:
        glm::vec4 m_rect{0};
    };

    ScreenMain::ScreenMain(IController *c) : IScreen(c){

    }

    void ScreenMain::onCreate(){
        switchDialog();
    }

    void ScreenMain::onClear(){

    }

    void ScreenMain::onDraw(Renderer &r){
        r.clear(0xFF000000);
    }

    void ScreenMain::onUpdate(float dt){

    }

    void ScreenMain::onResize(int w, int h) {

    }

    void ScreenMain::switchDialog() {
        controller()->show(new TestDialog(controller()));
    }

    void ScreenMain::onKey(int k, int a, int m){
        if (k == GLFW_KEY_SPACE && a == GLFW_PRESS) {
            switchDialog();
        }
    }

    void ScreenMain::onCursor(float x, float y){

    }

}
