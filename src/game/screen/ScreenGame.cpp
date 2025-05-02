#include "tetrablocks/game/screen/ScreenGame.hpp"

#include <format>
#include <GLFW/glfw3.h>

#include "tetrablocks/Constants.hpp"
#include "tetrablocks/Utils.hpp"
#include "tetrablocks/game/dialog/DialogPause.hpp"

namespace tetrablocks {

    ScreenGame::ScreenGame(IController *c) : IScreen(c),
        m_random(std::make_unique<std::mt19937_64>(std::random_device{}())),m_pause(c), m_cell(50) {
        for (auto&[item, pos] : m_shapes) {
            item = Shape::getRandom(getRandom());
            pos = {0,0};
        }
    }

    void ScreenGame::onCreate(){
        m_pause.onCreate("Pause",[this]{
            controller()->show(new DialogPause(controller()));
        });
    }

    void ScreenGame::onClear(){
        m_pause.onClear();
    }

    void ScreenGame::draw(Renderer &r, ShapeItem& s, const bool selected) const {
        const auto point = (selected ? m_mouse : s.pos) - (glm::vec2(s.item.getSize()) * m_cell) / 2.f;
        for (int x = 0; x < s.item.getSize().x; x++) {
            for (int y = 0; y < s.item.getSize().y; y++) {
                if (const auto block = s.item.at({x,y}); block != Block::Empty) {
                    r.fill(getColor(block));
                    r.rect(
                        point.x + m_cell.x * static_cast<float>(x),
                        point.y + m_cell.y * static_cast<float>(y),
                        m_cell.x,
                        m_cell.y
                    );
                }
            }
        }
    }

    void ScreenGame::drawBoard(Renderer &r) {
        const auto& origin = m_pos_board;
        const auto size = m_cell * glm::vec2(m_board.getSize()) + 2 * GRID_PADDING;
        r.fill(0xFFFFFFFF);
        r.rect(origin.x - GRID_PADDING,origin.y - GRID_PADDING,size.x,size.y);


        forXY (m_board.getSize(),[this, origin, &r](const glm::vec2& p) {
            const auto block = m_board.at(p);
            auto offset = origin + p * m_cell;
            r.fill(getColor(block));
            r.rect(offset.x,offset.y,m_cell.x,m_cell.y);
        });


        r.fill(0xFFFFFFFF);
        for (int i = 1; i < m_board.getSize().x;i++) {
            r.rect(origin.x + m_cell.x * i,origin.y,1,m_board.getSize().y * m_cell.y);
        }
        for (int i = 1; i < m_board.getSize().y;i++) {
            r.rect(origin.x ,origin.y+ m_cell.y * i,m_board.getSize().x * m_cell.x,1);
        }
    }

    void ScreenGame::onDraw(Renderer &r){
        r.clear(COLOR_BG);

        m_pause.onDraw(r);
        r.fill(COLOR_TEXT);
        r.text(controller()->getAssets().m_font,std::format("{}", m_score),m_pos_score,Align::Center);

        drawBoard(r);

        for (int i = 0; i < 3; i++) {
            draw(r,m_shapes[i],i == m_selected);
        }
    }

    void ScreenGame::onUpdate(float dt){}

    void ScreenGame::onResize(const int w, const int h) {
        const auto rect_header = glm::vec4{0,0,w,h*0.10};
        const auto rect_board  = glm::vec4{0,rect_header.w,w,h*0.7};
        const auto rect_footer = glm::vec4{0,rect_header.w + rect_board.w,w,h*0.20};

        m_pos_score = {rect_header.z / 2.f,rect_header.w / 2.f + static_cast<float>(controller()->getAssets().m_font.getSize()) / 2.f};
        m_pause.pos = glm::vec2{50.f,rect_header.w / 2.f - m_pause.getSize().y / 2.f};

        const auto side = std::min(rect_board.z,rect_board.w);
        //m_cell = glm::vec2{side} / glm::vec2(m_board.getSize());

        m_pos_board = glm::vec2{rect_board.x + rect_board.z / 2.f,rect_board.y + rect_board.w / 2.f} - (glm::vec2(m_board.getSize()) * m_cell) / 2.f;

        for (int i = 0; i < 3; i++) {
            m_shapes[i].pos = {rect_footer.x + w * (0.3 + 0.2 * i),rect_footer.y + rect_footer.w / 2.f};
        }

    }

    void ScreenGame::onKey(const int k, const int a, const int m){
        if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
            controller()->show(new DialogPause(controller()));
        }
        if (k == GLFW_MOUSE_BUTTON_LEFT) {
            if (a == GLFW_PRESS) {
                for (int i = 0; i < 3; i++) {
                    if (glm::distance(m_shapes[i].pos, m_mouse) <= glm::length(m_cell)) {
                        m_selected = i;
                    }
                }
            }
            if (a == GLFW_RELEASE){
                m_selected = -1;
            }
        }
        m_pause.onKey(k,a,m);
    }

    void ScreenGame::onCursor(const float x, const float y){
        m_mouse = glm::vec2{x,y};
        m_pause.onCursor(x,y);
    }

    uint ScreenGame::getRandom() const {
        if (m_random) {
            return static_cast<uint>((*m_random)());
        }
        return -1;
    }
}
