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

MapConstructor& MapConstructor::spawnRivers(std::map<Tile::Type, double> probabilities) {
    model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type) && probabilities.count(tile.type)) {
            if (((*generator_)() % 1000) / 1000.0 < probabilities.at(tile.type)) {
                tile.type = Tile::Type::River;
            }
        }
    });

    return *this;
}

MapConstructor& MapConstructor::createRiverFlow() {
    auto sources = model_.getTiles(Tile::Type::River);

    for (const auto& source : sources) {
        for (auto lowestNeighbor = findLowestNeighbor(source), current = std::const_pointer_cast<Tile>(source);
            lowestNeighbor->type != Tile::Type::Water && lowestNeighbor->type != Tile::Tile::River;
            current = lowestNeighbor,
            lowestNeighbor = findLowestNeighbor(lowestNeighbor))
        {
            const IntIsoPoint currentCoords(current->coords.toIsometric());
            const IntIsoPoint neighCoords(lowestNeighbor->coords.toIsometric());

            if (heightMap_(neighCoords.y, neighCoords.x)
                <= heightMap_(currentCoords.y, currentCoords.x))
            {
                lowestNeighbor->type = Tile::Type::River;
            } else {
                spawnLake(current);
                break;
            }
        }
    }

    return *this;
}

void MapConstructor::spawnLake(std::shared_ptr<Tile> source) {
    unsigned maxSize = 1 + (*generator_)() % 5;

    for (unsigned i = 0; i < maxSize; ++i) {
        source->type = Tile::Type::Water;
        auto neighbors = model_.getAdjacentNeighbors(source);
        source = std::const_pointer_cast<Tile>(neighbors[(*generator_)() % neighbors.size()]);
    }
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
