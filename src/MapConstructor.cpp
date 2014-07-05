/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
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
{
    model_.getTile(IntIsoPoint(0, 1))->units.push(tileenums::Unit::Phalanx);
}

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

MapConstructor& MapConstructor::setTypeMask(const std::vector<tileenums::Type>& typesToTransform) {
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
            current->type != tileenums::Type::Water;
            current = lowestNeighbor,
            lowestNeighbor = findLowestNeighbor(lowestNeighbor))
        {
            const IntIsoPoint currentCoords(current->coords.toIsometric());
            const IntIsoPoint lowestNeighborCoords(lowestNeighbor->coords.toIsometric());

            if (model_.isInBounds(lowestNeighbor)) {
                current->attributes.river->addDirection(current->getDirection(lowestNeighbor));
                lowestNeighbor->attributes.river.enable();
                lowestNeighbor->attributes.river->addDirection(lowestNeighbor->getDirection(current));
            } else {
                current->type = tileenums::Type::Water;
                break;
            }

            if (heightMap_(lowestNeighborCoords.y, lowestNeighborCoords.x)
                > heightMap_(currentCoords.y, currentCoords.x))
            {
                current->type = tileenums::Type::Water;
                break;
            }
        }
    }

    return *this;
}

std::shared_ptr<Tile> MapConstructor::findLowestNeighbor(std::shared_ptr<const Tile> tile) const {
    std::shared_ptr<const Tile> res;

    auto neighbors = tile->getAdjacentNeighbors();
    for (const auto& neighbor : neighbors) {
        if (!res) {
            res = neighbor;
        } else {
            const IntIsoPoint resCoords(res->coords.toIsometric());
            const IntIsoPoint neighCoords(neighbor->coords.toIsometric());
            res = (heightMap_(resCoords.y, resCoords.x) < heightMap_(neighCoords.y, neighCoords.x))?
                res : neighbor;
        }
    }

    return std::const_pointer_cast<Tile>(res);
}


MapModel MapConstructor::construct() const {
    return model_;
}

MapConstructor& MapConstructor::setType(tileenums::Type type, double threshold) {
    model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type)) {
            IntIsoPoint coords(tile.coords.toIsometric());
            if (heightMap_(coords.y, coords.x) >= threshold)
                tile.type = type;
        }
    });

    return *this;
}

bool MapConstructor::isTypeModifiable(tileenums::Type type) const {
    return std::find(typeMask_.begin(), typeMask_.end(), type) != typeMask_.end();
}
