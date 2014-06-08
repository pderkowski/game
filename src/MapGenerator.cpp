/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include <vector>
#include "MapModel.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "MapConstructor.hpp"
#include "Tile.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    auto landMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 0.5);
    auto hillMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 1);
    auto mountainMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 1);

    const double waterLevel = landMap.min();
    const double landLevel = landMap.getNth(0.75 * landMap.getSize());
    const double hillLevel = hillMap.getNth(0.85 * hillMap.getSize());
    const double mountainLevelOnPlains = mountainMap.getNth(0.99 * mountainMap.getSize());
    const double mountainLevelOnHills = mountainMap.getNth(0.80 * mountainMap.getSize());

    return MapConstructor(landMap)
        .setTypeMask({ Tile::Type::Empty })
        .setType(Tile::Type::Water, waterLevel)
        .setTypeMask({ Tile::Type::Water })
        .setType(Tile::Type::Plains, landLevel)
        .setSource(hillMap)
        .setTypeMask({ Tile::Type::Plains })
        .setType(Tile::Type::Hills, hillLevel)
        .setSource(mountainMap)
        .setTypeMask({ Tile::Type::Plains })
        .setType(Tile::Type::Mountains, mountainLevelOnPlains)
        .setTypeMask({ Tile::Type::Hills })
        .setType(Tile::Type::Mountains, mountainLevelOnHills)
        .construct();
}
