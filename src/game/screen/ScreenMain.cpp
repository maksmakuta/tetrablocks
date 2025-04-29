#include "tetrablocks/game/screen/ScreenMain.hpp"
#include "tetrablocks/game/core/IDialog.hpp"

namespace tetrablocks {

    ScreenMain::ScreenMain(IController *c) : IScreen(c){

    }

    void ScreenMain::onCreate(){

    }

    void ScreenMain::onClear(){

    }

    void ScreenMain::onDraw(Renderer &r){
        r.clear(0xFF1D1D7C);
    }

    void ScreenMain::onUpdate(float dt){

    }

    void ScreenMain::onResize(int w, int h) {
        m_view = {w,h};
    }

    void ScreenMain::onKey(int k, int a, int m){

    }

    void ScreenMain::onCursor(float x, float y){

    }

}
