/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPCONSTRUCTOR_HPP_
#define MAPCONSTRUCTOR_HPP_

#include <vector>
#include <functional>
#include "Tile.hpp"
#include "MapModel.hpp"
#include "HeightMap.hpp"

class MapConstructor {
public:
    MapConstructor(const HeightMap& heightMap);

    MapConstructor(const MapConstructor&) = delete;
    MapConstructor& operator =(const MapConstructor&) = delete;

    MapConstructor& setSource(const HeightMap& heightMap);
    MapConstructor& setTypeMask(const std::vector<Tile::Type>& modifiableTypes);

    MapModel construct() const;

    MapConstructor& setType(Tile::Type type, double threshold);
    MapConstructor& setType(Tile::Type type, std::function<bool(double)> predicate);

private:
    bool isTypeModifiable(Tile::Type type) const;

    HeightMap heightMap_;
    MapModel model_;
    std::vector<Tile::Type> typeMask_;
};

#endif  // MAPCONSTRUCTOR_HPP_
