#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "Matcher.hpp"
#include "TileEnums.hpp"

Matcher::Matcher(Predicate predicate)
    : predicate_(predicate)
{ }

bool Matcher::match(std::shared_ptr<const Tile> tile) const {
    return predicate_(tile);
}


TileTypeMatcher::TileTypeMatcher(tileenums::Type type)
    : Matcher([type] (std::shared_ptr<const Tile> tile) {
        return tile->type == type;
    })
{ }

NeighborTypesMatcher::NeighborTypesMatcher(tileenums::Type type, const NeighborTypes& neighborTypes)
    : Matcher([type, neighborTypes] (std::shared_ptr<const Tile> tile) {
        auto neighbors = tile->getNeighbors();
        if (tile->type != type || neighbors.size() != neighborTypes.size())
            return false;

        for (unsigned i = 0; i < neighborTypes.size(); ++i) {
            switch (neighborTypes[i]) {
                case Any:
                    break;
                case Same:
                    if (neighbors[i]->type == type)
                        break;
                    else
                        return false;
                case Different:
                    if (neighbors[i]->type != type)
                        break;
                    else
                        return false;
            }
        }

        return true;
    })
{ }
