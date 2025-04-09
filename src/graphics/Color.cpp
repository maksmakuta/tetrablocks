#include "Color.hpp"

namespace tetrablocks::graphics {

    Color::Color(const glm::uint hex) : m_color(hex){}

    Color::Color(const glm::vec3& _vec3){
        m_color |= 0xFF << 24;
        m_color |= static_cast<glm::uint>(_vec3.r * 255.f) << 16;
        m_color |= static_cast<glm::uint>(_vec3.g * 255.f) <<  8;
        m_color |= static_cast<glm::uint>(_vec3.b * 255.f) <<  0;
    }

    Color::Color(const glm::vec4& _vec4) : Color(){
        m_color |= static_cast<glm::uint>(_vec4.a * 255.f) << 24;
        m_color |= static_cast<glm::uint>(_vec4.r * 255.f) << 16;
        m_color |= static_cast<glm::uint>(_vec4.g * 255.f) <<  8;
        m_color |= static_cast<glm::uint>(_vec4.b * 255.f) <<  0;
    }

    Color::Color(const float red,const float green,const float blue, const float alpha)
        : Color(glm::vec4{red,green,blue,alpha}){}


    float Color::getAlpha() const{
        return static_cast<float>(m_color >> 24 & 0xFF) / 255.f;
    }

    float Color::getRed() const{
        return static_cast<float>(m_color >> 16 & 0xFF) / 255.f;
    }

    float Color::getGreen() const{
        return static_cast<float>(m_color >> 8 & 0xFF) / 255.f;
    }

    float Color::getBlue() const{
        return static_cast<float>(m_color & 0xFF) / 255.f;
    }

    uint8_t Color::getIAlpha() const{
        return m_color >> 24 & 0xFF;
    }

    glm::uint Color::toHex() const {
        return m_color;
    }

    uint8_t Color::getIRed() const{
        return m_color >> 16 & 0xFF;
    }

    uint8_t Color::getIGreen() const{
        return m_color >> 8 & 0xFF;
    }

    uint8_t Color::getIBlue() const{
        return m_color & 0xFF;
    }

    glm::vec3 Color::toVec3() const{
        return {getRed(),getGreen(), getBlue()};
    }

    glm::vec4 Color::toVec4() const{
        return {getRed(),getGreen(), getBlue(),getAlpha()};
    }

}