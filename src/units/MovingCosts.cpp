#include <map>
#include "TileEnums.hpp"
#include "MovingCosts.hpp"
#include "Unit.hpp"

namespace units {


std::map<tileenums::Type, unsigned> getMovingCosts(units::Type type) {
    switch (type) {
    case units::Type::Phalanx:
        return std::map<tileenums::Type, unsigned>{
            { tileenums::Type::Empty, UINT_MAX },
            { tileenums::Type::Water, UINT_MAX },
            { tileenums::Type::Grassland, 1 },
            { tileenums::Type::Plains, 1 },
            { tileenums::Type::Forest, 2 },
            { tileenums::Type::Desert, 1 },
            { tileenums::Type::Hills, 2 },
            { tileenums::Type::Mountains, UINT_MAX }
        };
    default:
        throw std::logic_error("Not implemented.");
    }
}


}  // namespace units
