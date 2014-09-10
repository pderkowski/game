#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <memory>
#include "map/Tile.hpp"
#include "Matcher.hpp"
#include "TileEnums.hpp"

using namespace tileenums;


namespace textures {


TileTypeMatcher::TileTypeMatcher(Type type)
    : Matcher<map::Tile>([type] (const map::Tile& tile) {
        return tile.type == type;
    })
{ }

NeighborTypesMatcher::NeighborTypesMatcher(Type type, const NeighborTypes& neighborTypes)
    : Matcher<map::Tile>([type, neighborTypes] (const map::Tile& tile) {
        if (tile.type != type)
            return false;

        std::vector<Direction> directions = { Direction::Top, Direction::TopRight, Direction::Right,
            Direction::BottomRight, Direction::Bottom, Direction::BottomLeft, Direction::Left,
            Direction::TopLeft };

        if (directions.size() != neighborTypes.size())
            throw std::invalid_argument("Incorrect size of neighborTypes vector.");

        for (unsigned i = 0; i < neighborTypes.size(); ++i) {
            switch (neighborTypes[i]) {
                case Any:
                    break;
                case Same:
                    if ((tile.hasNeighbor(directions[i]) && tile.getNeighbor(directions[i]).type == type)
                        || !tile.hasNeighbor(directions[i]))
                    {
                        break;
                    }
                    else
                        return false;
                case Different:
                    if (tile.hasNeighbor(directions[i]) && tile.getNeighbor(directions[i]).type != type)
                        break;
                    else
                        return false;
            }
        }

        return true;
    })
{ }


AlwaysMatcher::AlwaysMatcher()
    : Matcher<map::Tile>([] (__attribute__((unused)) const map::Tile& tile) {
        return true;;
    })
{ }

}  // namespace textures
