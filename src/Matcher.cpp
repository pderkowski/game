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
    : Matcher([&] (std::shared_ptr<const Tile> tile,
        __attribute__((unused)) const std::vector<std::shared_ptr<const Tile>>& neighbors)
    {
        return tile->type == type_;
    }),
    type_(type)
{ }


NeighborTypesMatcher::NeighborTypesMatcher(Tile::Type type, const NeighborTypes& neighborTypes)
    : Matcher([&] (std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors)
    {
        if (tile->type != type_ || neighbors.size() != neighborTypes_.size())
            return false;

        for (unsigned i = 0; i < neighborTypes_.size(); ++i) {
            switch (neighborTypes_[i]) {
                case Any:
                    break;
                case Same:
                    if (neighbors[i]->type == type_)
                        break;
                    else
                        return false;
                case Different:
                    if (neighbors[i]->type != type_)
                        break;
                    else
                        return false;
            }
        }

        return true;
    }),
    type_(type),
    neighborTypes_(neighborTypes)
{ }
