/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include <vector>
#include "Tile.hpp"
#include "MapModel.hpp"

class MapGenerator {
public:
    static MapModel generateMap(int rows, int columns);
};

#endif  // MAPGENERATOR_HPP_
