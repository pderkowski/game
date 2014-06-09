/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "MapModel.hpp"
#include "MapConstructor.hpp"

MapConstructor::MapConstructor(const HeightMap& heightMap)
    : heightMap_(heightMap), model_(heightMap.getRowsNo(), heightMap.getColumnsNo())
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

MapConstructor& MapConstructor::setType(Tile::Type type, std::function<bool(double)> predicate) {
        model_.changeTiles([&] (Tile& tile) {
        if (isTypeModifiable(tile.type)) {
            IntIsoPoint coords(tile.coords.toIsometric());
            if (predicate(heightMap_(coords.y, coords.x)))
                tile.type = type;
        }
    });

    return *this;
}

bool MapConstructor::isTypeModifiable(Tile::Type type) const {
    return std::find(typeMask_.begin(), typeMask_.end(), type) != typeMask_.end();
}
