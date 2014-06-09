/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include <vector>
#include <cmath>
#include "MapModel.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "MapConstructor.hpp"
#include "Tile.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    auto landMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 1);
    auto humidityMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 2, 0.6);
    auto hillMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 4);
    auto mountainMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)(), 8, 0.4);

    const double waterLevel = landMap.min();
    const double landLevel = landMap.getNth(0.70 * landMap.getSize());
    const double plainsLevel = humidityMap.getNth(0.60 * humidityMap.getSize());
    const double desertLevel = humidityMap.getNth(0.90 * humidityMap.getSize());
    const double hillLevel = hillMap.getNth(0.85 * hillMap.getSize());
    const double mountainLevelOnPlains = mountainMap.getNth(0.99 * mountainMap.getSize());
    const double mountainLevelOnHills = mountainMap.getNth(0.80 * mountainMap.getSize());

    const std::vector<Tile::Type> landTypes = { Tile::Type::Grassland, Tile::Type::Plains,
        Tile::Type::Desert, Tile::Type::Hills, Tile::Type::Mountains };

    return MapConstructor(landMap)
        .setTypeMask({ Tile::Type::Empty })
        .setType(Tile::Type::Water, waterLevel)
        .setTypeMask({ Tile::Type::Water })
        .setType(Tile::Type::Grassland, landLevel)
        .setTypeMask(landTypes)
        .setSource(humidityMap)
        .setType(Tile::Type::Plains, plainsLevel)
        .setType(Tile::Type::Desert, desertLevel)
        .setSource(hillMap)
        .setType(Tile::Type::Hills, hillLevel)
        .setSource(mountainMap)
        .setType(Tile::Type::Mountains, mountainLevelOnPlains)
        .setTypeMask({ Tile::Type::Hills })
        .setType(Tile::Type::Mountains, mountainLevelOnHills)
        .construct();
}
