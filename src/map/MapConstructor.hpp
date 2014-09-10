/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_MAPCONSTRUCTOR_HPP_
#define MAP_MAPCONSTRUCTOR_HPP_

#include <vector>
#include "Tile.hpp"
#include "MapModel.hpp"
#include "HeightMap.hpp"
#include "Attributes.hpp"
#include "TileEnums.hpp"


namespace map {


class MapConstructor {
public:
    explicit MapConstructor(const HeightMap& heightMap);

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
    Tile* findRandomLowerNeighbor(Tile* tile);
    Tile* findLowest(std::vector<Tile*> tiles) const;
    bool isHigherThanNeighbors(const Tile& tile) const;
    bool doesNotBorderWater(const Tile& tile) const;

    HeightMap heightMap_;
    MapModel model_;
    std::vector<tileenums::Type> typeMask_;
};


}  // namespace map


#endif  // MAP_MAPCONSTRUCTOR_HPP_
