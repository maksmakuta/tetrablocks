#include "tetrablocks/game/screen/ScreenGame.hpp"

namespace tetrablocks {

    ScreenGame::ScreenGame(IController *c) : IScreen(c){

    }

    void ScreenGame::onCreate(){

    }

    void ScreenGame::onClear(){

    }

    void ScreenGame::onDraw(Renderer &r){
        r.clear(COLOR_BG);
    }

    void ScreenGame::onUpdate(float dt){

    }

    void ScreenGame::onResize(int w, int h) {

    }

    void ScreenGame::onKey(int k, int a, int m){

    }

    void ScreenGame::onCursor(float x, float y){

    }

}
