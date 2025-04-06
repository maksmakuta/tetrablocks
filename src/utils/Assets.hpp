#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <string>

namespace tetrablocks::utils {

    class Assets {
    public:
        explicit Assets(std::string root = TETRABLOCKS_ASSETS_PATH);

        [[nodiscard]] std::string getFont(const std::string& font_name) const;
        [[nodiscard]] std::string getShader(const std::string& shader_name) const;
        [[nodiscard]] std::string getTexture(const std::string& texture_name) const;

    private:
        std::string m_root;
    };

}

#endif //ASSETS_HPP
