#include "tetrablocks/game/screen/ScreenGame.hpp"

#include <format>
#include <GLFW/glfw3.h>

#include "tetrablocks/Utils.hpp"
#include "tetrablocks/game/dialog/DialogPause.hpp"

namespace tetrablocks {

    ScreenGame::ScreenGame(IController *c) : IScreen(c), m_pause(c) {}

    void ScreenGame::onCreate(){
        m_pause.onCreate("Pause",[this]{
            controller()->show(new DialogPause(controller()));
        });
    }

    void ScreenGame::onClear(){
        m_pause.onClear();
    }

    void ScreenGame::onDraw(Renderer &r){
        r.clear(COLOR_BG);

        drawHeader(r,m_rect_header);
        drawBoard(r,m_rect_board);
        drawShapes(r,m_rect_shapes);
    }

    void ScreenGame::drawHeader(Renderer& r, const glm::vec4& rect){
        const auto center = glm::vec2{rect.x + rect.z / 2.f,rect.y + rect.w / 2.f};

        r.fill(COLOR_TEXT);
        r.text(controller()->getAssets().m_font, std::format("Score: {}",m_score),center,Align::Center);

        m_pause.onDraw(r);
    }

    void ScreenGame::drawBoard(Renderer& r, const glm::vec4& rect) {
        r.fill(COLOR_GRID_BORDER);
        r.rect(rect.x,rect.y,rect.z,rect.w);

        const auto origin = glm::vec2{rect.x,rect.y} + GRID_PADDING;
        const auto size = glm::vec2{rect.z,rect.w} - GRID_PADDING;
        const auto cell = size / glm::vec2(m_board.getSize());

        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                const auto pos = glm::vec2{x,y};
                const auto offset = origin + pos * cell;
                const auto block = m_board.at(pos);
                r.fill(getColor(block));
                r.rect(offset.x,offset.y,cell.x - GRID_PADDING,cell.y - GRID_PADDING);
            }
        }
    }

    void drawShape(Shape& s, const glm::vec2& offset) {

    }

    void ScreenGame::drawShapes(Renderer& r, const glm::vec4& rect){

    }

    void ScreenGame::onUpdate(float dt){}

    void ScreenGame::onResize(int w, int h) {
        m_view = {w,h};

        const auto side = static_cast<float>(std::min(w,h));
        m_rect_header = {0,0,m_view.x,side*0.15f};
        m_rect_shapes = {0,m_view.y - side*0.35f,m_view.x,side*0.35f};

        m_pause.pos = glm::vec2(m_rect_header.w / 2.f - m_pause.getSize().y / 2.f);

        const auto side2 = static_cast<float>(std::min(m_view.x,m_view.y - (m_rect_header.w + m_rect_shapes.w)));
        m_rect_board = {m_view.x / 2.f - side2 / 2.f,m_rect_header.w,side2,side2};
    }

    void ScreenGame::onKey(const int k, const int a, const int m){
        if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
            controller()->show(new DialogPause(controller()));
        }
        m_pause.onKey(k,a,m);
    }

    void ScreenGame::onCursor(float x, float y){
        m_mouse = {x,y};
        m_pause.onCursor(x,y);
    }

}
