#include "Button.hpp"

namespace tetrablocks::ui {

    void Button::onCreate(const utils::Assets& assets, const std::string& name) {
        m_image.loadPNG(assets.getTexture(name));
        m_image.setWrap(graphics::TextureWrap::Repeat);
        m_image.setMagFilter(graphics::TextureFilter::Nearest);
        m_image.setMinFilter(graphics::TextureFilter::Linear);
        m_image.genMipmaps();
    }

    void Button::onClear(){
        m_image.deinit();
    }

    void Button::onDraw(graphics::Canvas& c){
        c.fill(graphics::Color(0xFF808080));
        c.circle(getPos() + getSize() / 2.f,getSize().x );

        c.fill(m_image);
        c.rect(getPos(),getSize());
    }

    void Button::onUpdate(float delta){

    }


}