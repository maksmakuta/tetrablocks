#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "tetrablocks/graphics/Font.hpp"

namespace tetrablocks {

    struct Assets {
        Font m_font_title{64};
        Font m_font_small{18};
        Font m_font{48};

        void init(const std::string& path) {
            m_font.load(path);
            m_font_title.load(path);
            m_font_small.load(path);
        }
    };

}

#endif //ASSETS_HPP
