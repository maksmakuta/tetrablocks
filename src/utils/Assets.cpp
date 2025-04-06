#include "Assets.hpp"

#include <utility>

namespace tetrablocks::utils {

    Assets::Assets(std::string root) : m_root(std::move(root)) {}

    std::string Assets::getFont(const std::string& font_name) const {
        return m_root + "fonts/" + font_name;
    }

    std::string Assets::getShader(const std::string& shader_name) const {
        return m_root + "shaders/" + shader_name;
    }

    std::string Assets::getTexture(const std::string& texture_name) const {
        return m_root + "textures/" + texture_name;
    }

}
