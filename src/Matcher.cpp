#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "Matcher.hpp"

Matcher::Matcher(Predicate predicate)
    : predicate_(predicate)
{ }

bool Matcher::match(std::shared_ptr<const Tile> tile,
    const std::vector<std::shared_ptr<const Tile>>& neighbors) const
{
    return predicate_(tile, neighbors);
}


TileMatcher::TileMatcher(std::function<bool(std::shared_ptr<const Tile>)> predicate)
    : Matcher([predicate] (std::shared_ptr<const Tile> tile,
        __attribute__((unused)) const std::vector<std::shared_ptr<const Tile>>& neighbors)
    {
        return predicate(tile);
    })
{ }


TileTypeMatcher::TileTypeMatcher(Tile::Type type)
    : Matcher([type] (std::shared_ptr<const Tile> tile,
        __attribute__((unused)) const std::vector<std::shared_ptr<const Tile>>& neighbors)
    {
        return tile->type == type;
    })
{ }


NeighborTypesMatcher::NeighborTypesMatcher(Tile::Type type, const NeighborTypes& neighborTypes)
    : Matcher([type, neighborTypes] (std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors)
    {
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
