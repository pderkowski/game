/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <chrono>
#include <memory>
#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "MapGenerator.hpp"
#include "NoiseGenerator.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    static auto generator = std::make_shared<std::default_random_engine>(
        std::chrono::system_clock::now().time_since_epoch().count());

    // NoiseGenerator noiseGenerator(generator);
    // auto probabilityMap = noiseGenerator.generateHeightMap(rows, columns);
    // probabilityMap
    //     .scale(2)
    //     .rise(2)
    //     .exp2()
    //     .round();
    // return MapModel(probabilityMap,
    //     [] (double height) {
    //         if (height <= 0) {
    //             return Tile::Type::Water;
    //         } else if (height <= 6) {
    //             return Tile::Type::Plains;
    //         } else if (height <= 7.5) {
    //             return Tile::Type::Hills;
    //         } else {
    //             return Tile::Type::Mountains;
    //         }
    //     });

    MapConstructor constructor(rows, columns, generator);
    constructor.spawnContinent(1000);
    constructor.spawnContinent(600);
    return constructor.getMapModel();
}
