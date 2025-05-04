#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP

#include "tetrablocks/model/Shape.hpp"
#include <random>

namespace tetrablocks {

    class ShapeFactory {
    public:
        explicit ShapeFactory(glm::uint seed = 0);
        Shape getNext();

    private:
        Block genColor();

        std::ranlux48 m_generator;
    };

}
#endif //SHAPEFACTORY_HPP
