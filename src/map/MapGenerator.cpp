/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <cmath>
#include "MapModel.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "MapConstructor.hpp"
#include "Tile.hpp"
#include "TileEnums.hpp"
#include "global/Random.hpp"


namespace map {


MapModel MapGenerator::generateMap(int rows, int columns) {
    auto landMap = NoiseGenerator::generateHeightMap(rows, columns, global::Random::getNumber(), 1, 0.5);
    auto humidityMap = NoiseGenerator::generateHeightMap(rows, columns, global::Random::getNumber(), 2, 0.6);
    auto hillMap = NoiseGenerator::generateHeightMap(rows, columns, global::Random::getNumber(), 4);
    auto mountainMap = NoiseGenerator::generateHeightMap(rows, columns, global::Random::getNumber(), 8, 0.4);
    auto forestMap = NoiseGenerator::generateHeightMap(rows, columns, global::Random::getNumber(), 4, 0.8);

    const double waterLevel = landMap.min();
    const double landLevel = landMap.getNth(0.70 * landMap.getSize());
    const double plainsLevel = humidityMap.getNth(0.60 * humidityMap.getSize());
    const double desertLevel = humidityMap.getNth(0.90 * humidityMap.getSize());
    const double hillLevel = hillMap.getNth(0.85 * hillMap.getSize());
    const double mountainLevelOnPlains = mountainMap.getNth(0.99 * mountainMap.getSize());
    const double mountainLevelOnHills = mountainMap.getNth(0.80 * mountainMap.getSize());
    const double forestLevel = forestMap.getNth(0.50 * forestMap.getSize());

    const std::vector<tileenums::Type> landTypes = { tileenums::Type::Grassland, tileenums::Type::Plains,
        tileenums::Type::Desert, tileenums::Type::Hills, tileenums::Type::Mountains };

    return MapConstructor(landMap)
        .setTypeMask({ tileenums::Type::Empty })
        .setType(tileenums::Type::Water, waterLevel)
        .setTypeMask({ tileenums::Type::Water })
        .setType(tileenums::Type::Grassland, landLevel)
        .setTypeMask(landTypes)
        .setSource(humidityMap)
        .setType(tileenums::Type::Plains, plainsLevel)
        .setType(tileenums::Type::Desert, desertLevel)
        .setSource(hillMap)
        .setType(tileenums::Type::Hills, hillLevel)
        .setSource(mountainMap)
        .setType(tileenums::Type::Mountains, mountainLevelOnPlains)
        .setTypeMask({ tileenums::Type::Hills })
        .setType(tileenums::Type::Mountains, mountainLevelOnHills)
        .setTypeMask({ tileenums::Type::Mountains, tileenums::Type::Hills, tileenums::Type::Grassland })
        .setSource(landMap)
        .spawnRivers(0.3)
        .createRiverFlow()
        .setSource(forestMap)
        .setTypeMask({ tileenums::Type::Plains, tileenums::Type::Grassland })
        .setType(tileenums::Type::Forest, forestLevel)
        .construct();
}


}  // namespace map
