/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <ctime>
#include "Map.hpp"
#include "MapGenerator.hpp"

Map MapGenerator::generateMap(int rows, int columns) {
    Map res(rows, columns);

    srand(time(NULL));

    for (int r = 0; r < res.getRowsNo(); ++r) {
        for (int c = 0; c < res.getColumnsNo(); ++c) {
            res.tile(r, c).setType(static_cast<Tile::Type>(rand() % Tile::NumberOfTileTypes));
        }
    }

    return res;
}
