/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "MapGenerator.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    MapConstructor constructor(rows, columns, generator);
    constructor.spawnContinent(1500);
    constructor.spawnContinent(1500);
    return constructor.getMapModel();
}
