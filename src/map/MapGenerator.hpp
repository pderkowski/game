/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_MAPGENERATOR_HPP_
#define MAP_MAPGENERATOR_HPP_

#include <vector>
#include "Tile.hpp"
#include "MapModel.hpp"


namespace map {


class MapGenerator {
public:
    static MapModel generateMap(int rows, int columns);
};


}  // namespace map

#endif  // MAP_MAPGENERATOR_HPP_
