#include "TetraGame.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/gl/gl.h"

namespace tetrablocks::game {

    void TetraGame::init(){
        glClearColor(0.25f, 0.34f, 0.39f, 1.0f);
    }

    void TetraGame::clear(){

 }

    void TetraGame::draw(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TetraGame::update(const float delta){

    }

    void TetraGame::onResize(const int w, const int h){
        glViewport(0,0,w,h);
        m_proj = glm::ortho(0.f,static_cast<float>(w),static_cast<float>(h),0.f);
    }

    void TetraGame::onCursor(float x, float y) {
        m = {x,y};
    }

    void TetraGame::onKey(int k, int a, int m){

    }
}
