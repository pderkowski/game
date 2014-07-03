/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <algorithm>
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "Attributes.hpp"

MapConstructor::MapConstructor(const HeightMap& heightMap,
    std::shared_ptr<std::default_random_engine> generator)
        : heightMap_(heightMap),
        model_(heightMap.getRowsNo(), heightMap.getColumnsNo()),
        generator_(generator)
{ }

MapConstructor& MapConstructor::setSource(const HeightMap& heightMap) {
    if (heightMap.getRowsNo() == heightMap_.getRowsNo()
        && heightMap.getColumnsNo() == heightMap_.getColumnsNo())
    {
        heightMap_ = heightMap;
        return *this;
    } else {
        throw std::runtime_error("The dimensions of a new source are different than the old ones.");
    }
}

MapConstructor& MapConstructor::setTypeMask(const std::vector<Tile::Type>& typesToTransform) {
    typeMask_ = typesToTransform;
    return *this;
}

MapConstructor& MapConstructor::spawnRivers(double probability) {
    model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type)) {
            if (((*generator_)() % 1000) / 1000.0 < probability) {
                tile.attributes.river.enable();
            }
        }
    });

    return *this;
}

MapConstructor& MapConstructor::createRiverFlow() {
    auto sources = model_.getTiles([] (const Tile& tile) {
        return tile.attributes.river;
    });

    for (const auto& source : sources) {
        for (auto lowestNeighbor = findLowestNeighbor(source), current = std::const_pointer_cast<Tile>(source);
            current->type != Tile::Type::Water;
            current = lowestNeighbor,
            lowestNeighbor = findLowestNeighbor(lowestNeighbor))
        {
            const IntIsoPoint currentCoords(current->coords.toIsometric());
            const IntIsoPoint lowestNeighborCoords(lowestNeighbor->coords.toIsometric());

            if (model_.isInBounds(lowestNeighbor)) {
                current->attributes.river->addDirection(getDirection(current, lowestNeighbor));
                lowestNeighbor->attributes.river.enable();
                lowestNeighbor->attributes.river->addDirection(getDirection(lowestNeighbor, current));
            } else {
                current->type = Tile::Type::Water;
                break;
            }

            if (heightMap_(lowestNeighborCoords.y, lowestNeighborCoords.x)
                > heightMap_(currentCoords.y, currentCoords.x))
            {
                current->type = Tile::Type::Water;
                break;
            }
        }
    }

    return *this;
}

std::shared_ptr<Tile> MapConstructor::findLowestNeighbor(std::shared_ptr<const Tile> tile) const {
    std::shared_ptr<const Tile> res;

    auto neighbors = model_.getAdjacentNeighbors(tile);
    for (const auto& neighbor : neighbors) {
        if (model_.isInBounds(neighbor) && *neighbor != *tile) {
            if (!res) {
                res = neighbor;
            } else {
                const IntIsoPoint resCoords(res->coords.toIsometric());
                const IntIsoPoint neighCoords(neighbor->coords.toIsometric());
                res = (heightMap_(resCoords.y, resCoords.x) < heightMap_(neighCoords.y, neighCoords.x))?
                    res : neighbor;
            }

        }
    }

    return std::const_pointer_cast<Tile>(res);
}


MapModel MapConstructor::construct() const {
    return model_;
}

MapConstructor& MapConstructor::setType(Tile::Type type, double threshold) {
    model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type)) {
            IntIsoPoint coords(tile.coords.toIsometric());
            if (heightMap_(coords.y, coords.x) >= threshold)
                tile.type = type;
        }
    });

    return *this;
}

bool MapConstructor::isTypeModifiable(Tile::Type type) const {
    return std::find(typeMask_.begin(), typeMask_.end(), type) != typeMask_.end();
}

Attributes::RiverDirection MapConstructor::getDirection(std::shared_ptr<const Tile> from,
    std::shared_ptr<const Tile> to) const
{
    auto adjacent = model_.getAdjacentNeighbors(from);

    if (adjacent.size() != 4) {
        throw std::runtime_error("There are not enough adjacent neighbors.");
    }

    if (*to == *adjacent[0]) {
        return Attributes::RiverDirection::Top;
    } else if (*to == *adjacent[1]) {
        return Attributes::RiverDirection::Right;
    } else if (*to == *adjacent[2]) {
        return Attributes::RiverDirection::Bottom;
    } else if (*to == *adjacent[3]) {
        return Attributes::RiverDirection::Left;
    } else {
        throw std::invalid_argument("Points " + toString(from->coords) + " " + toString(to->coords)
            + " are not adjacent.");
    }
}
