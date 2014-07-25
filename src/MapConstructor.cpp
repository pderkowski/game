/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "Attributes.hpp"
#include "units/Unit.hpp"

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

MapConstructor& MapConstructor::setTypeMask(const std::vector<tileenums::Type>& typesToTransform) {
    typeMask_ = typesToTransform;
    return *this;
}

MapConstructor& MapConstructor::spawnRivers(double probability) {
    model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type)) {
            if ((((*generator_)() % 1000) / 1000.0 < probability)
                && isHigherThanNeighbors(tile)
                && doesNotBorderWater(tile))
            {
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
        for (auto lowerNeighbor = findRandomLowerNeighbor(source), current = source;
            current->type != tileenums::Type::Water;
            current = lowerNeighbor,
            lowerNeighbor = findRandomLowerNeighbor(lowerNeighbor))
        {
            if (!lowerNeighbor) {
                current->type = tileenums::Type::Water;
                break;
            } else if (lowerNeighbor->attributes.river) {
                current->attributes.river->addDirection(current->getDirection(*lowerNeighbor));
                lowerNeighbor->attributes.river->addDirection(lowerNeighbor->getDirection(*current));
                break;
            } else {
                lowerNeighbor->attributes.river.enable();
                current->attributes.river->addDirection(current->getDirection(*lowerNeighbor));
                lowerNeighbor->attributes.river->addDirection(lowerNeighbor->getDirection(*current));
            }
        }
    }

    return *this;
}

Tile* MapConstructor::findRandomLowerNeighbor(Tile* tile) {
    std::vector<Tile*> neighbors = tile->getAdjacentNeighbors();
    std::vector<Tile*> lowerNeighbors;

    std::copy_if(neighbors.begin(), neighbors.end(), std::back_inserter(lowerNeighbors),
        [tile, this] (Tile* neighbor) {
            const IntIsoPoint tileCoords(tile->coords.toIsometric());
            const IntIsoPoint neighCoords(neighbor->coords.toIsometric());
            return heightMap_(neighCoords.y, neighCoords.x) < (heightMap_(tileCoords.y, tileCoords.x));
        });

    if (lowerNeighbors.size() > 0) {
        lowerNeighbors.push_back(findLowest(lowerNeighbors)); // lowest has 2 times bigger chance
        return lowerNeighbors[(*generator_)() % lowerNeighbors.size()];
    } else {
        return nullptr;
    }
}

Tile* MapConstructor::findLowest(std::vector<Tile*> tiles) const
{
    Tile* lowest = tiles.front();

    for (Tile* tile : tiles) {
        const IntIsoPoint tileCoords(tile->coords.toIsometric());
        const IntIsoPoint lowestCoords(lowest->coords.toIsometric());

        if ((heightMap_(tileCoords.y, tileCoords.x) < heightMap_(lowestCoords.y, lowestCoords.x))) {
            lowest = tile;
        }
    }

    return lowest;
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

bool MapConstructor::isHigherThanNeighbors(const Tile& tile) const {
    const IntIsoPoint tileCoords(tile.coords.toIsometric());

    auto neighbors = tile.getAdjacentNeighbors();
    for (const auto& neighbor : neighbors) {
        const IntIsoPoint neighCoords(neighbor->coords.toIsometric());
        if (heightMap_(tileCoords.y, tileCoords.x) <= heightMap_(neighCoords.y, neighCoords.x)) {
            return false;
        }
    }

    return true;
}

bool MapConstructor::doesNotBorderWater(const Tile& tile) const {
    const IntIsoPoint tileCoords(tile.coords.toIsometric());

    auto neighbors = tile.getNeighbors();
    for (const auto& neighbor : neighbors) {
        if (neighbor->type == tileenums::Type::Water) {
            return false;
        }
    }

    return true;
}
