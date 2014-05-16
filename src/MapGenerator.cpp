/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include <cmath>
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "Gradient.hpp"
#include "Tile.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    auto probabilityMap = NoiseGenerator::generateHeightMap(rows, columns, (*generator)());
    Gradient gradient;
    gradient.addPoint(0.0, Tile::Type::Water);
    gradient.addPoint(0.75, Tile::Type::Plains);
    gradient.addPoint(0.96, Tile::Type::Hills);
    gradient.addPoint(0.995, Tile::Type::Mountains);
    return MapModel(probabilityMap, gradient);

    // MapConstructor constructor(rows, columns, generator);
    // constructor.spawnContinent(2000);
    // constructor.spawnContinent(600);
    // return constructor.getMapModel();
}
