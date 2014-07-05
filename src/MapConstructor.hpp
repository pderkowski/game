/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPCONSTRUCTOR_HPP_
#define MAPCONSTRUCTOR_HPP_

#include <vector>
#include <memory>
#include <random>
#include <map>
#include "Tile.hpp"
#include "MapModel.hpp"
#include "HeightMap.hpp"
#include "Attributes.hpp"
#include "TileEnums.hpp"

class MapConstructor {
public:
    MapConstructor(const HeightMap& heightMap,
        std::shared_ptr<std::default_random_engine> generator);

    MapConstructor(const MapConstructor&) = delete;
    MapConstructor& operator =(const MapConstructor&) = delete;

    MapConstructor& setSource(const HeightMap& heightMap);
    MapConstructor& setTypeMask(const std::vector<tileenums::Type>& modifiableTypes);

    MapConstructor& spawnRivers(double probability);
    MapConstructor& createRiverFlow();

    MapModel construct() const;

    MapConstructor& setType(tileenums::Type type, double threshold);

private:
    bool isTypeModifiable(tileenums::Type type) const;
    std::shared_ptr<Tile> findLowestNeighbor(std::shared_ptr<const Tile> tile) const;

    HeightMap heightMap_;
    MapModel model_;
    std::vector<tileenums::Type> typeMask_;
    std::shared_ptr<std::default_random_engine> generator_;
};

#endif  // MAPCONSTRUCTOR_HPP_
