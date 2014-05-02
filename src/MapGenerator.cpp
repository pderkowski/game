/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include <iostream>
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    NoiseGenerator noiseGenerator(generator);
    auto noiseMatrix = noiseGenerator.generateNoiseMatrix(rows, columns);
    noiseGenerator.scale(noiseMatrix, -1, 6);
    return MapModel(noiseMatrix,
        [] (double height) {
            if (height <= 0) {
                return Tile::Type::Water;
            } else if (height <= 2) {
                return Tile::Type::Plains;
            } else if (height <= 6) {
                return Tile::Type::Hills;
            } else {
                return Tile::Type::Mountains;
            }
        });

    // MapConstructor constructor(rows, columns, generator);
    // constructor.spawnContinent(1500);
    // constructor.spawnContinent(1500);
    // return constructor.getMapModel();
}
