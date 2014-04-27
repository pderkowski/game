/* Copyright 2014 <Piotr Derkowski> */

#include "MapModel.hpp"
#include "MapConstructor.hpp"
#include "MapGenerator.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    MapConstructor constructor(rows, columns);
    constructor.spawnContinent(1500);
    constructor.spawnContinent(1500);
    return constructor.getMapModel();
}
