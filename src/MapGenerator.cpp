/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <ctime>
#include <vector>
#include "Map.hpp"
#include "Tile.hpp"
#include "MapGenerator.hpp"

Map MapGenerator::generateMap(int rows, int columns) {
    srand(time(NULL));

    Map map(rows, columns);
    assignTileTypes(map);

    return map;
}

void MapGenerator::assignTileTypes(Map& map) {
    auto heights = generateHeights(map.getRowsNo(), map.getColumnsNo());

    for (unsigned r = 0; r < heights.size(); ++r) {
        for (unsigned c = 0; c < heights[r].size(); ++c) {
            map.tile(r, c).setType(convertHeightToTileType(heights[r][c]));
        }
    }
}

std::vector<std::vector<float>> MapGenerator::generateHeights(int rows, int columns) {
    std::vector<std::vector<float>> heights(rows, std::vector<float>(columns, 0));
    return heights;
}

Tile::Type MapGenerator::convertHeightToTileType(float height) {
    if (height <= 0) {
        return Tile::Type::Water;
    } else if (0 < height && height <= 2) {
        return Tile::Type::Plains;
    } else if (2 < height && height <= 4) {
        return Tile::Type::Hills;
    } else if (4 < height) {
        return Tile::Type::Mountains;
    } else {
        return Tile::Type::Empty;
    }
}
