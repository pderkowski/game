/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include "MapModel.hpp"
#include "Tile.hpp"
#include "MapGenerator.hpp"

MapModel MapGenerator::generateMap(int rows, int columns) {
    srand(time(NULL));

    MapModel model(rows, columns);
    assignTileTypes(model);

    return model;
}

void MapGenerator::assignTileTypes(MapModel& model) {
    auto heights = generateHeights(model.getRowsNo(), model.getColumnsNo());

    for (unsigned r = 0; r < heights.size(); ++r) {
        for (unsigned c = 0; c < heights[r].size(); ++c) {
            model.getTile(r, c)->type = convertHeightToTileType(heights[r][c]);
        }
    }
}

std::vector<std::vector<float>> MapGenerator::generateHeights(int rows, int columns) {
    auto heights = getInitialHeights(rows, columns);

    const int dotsNo = 1 * rows * columns;
    const int dotsPerHit = 4;
    for (int i = 0; i < dotsNo; ++i) {
        heights[rand() % rows][rand() % columns] += dotsPerHit;
    }

    for (int i = 0; i < 6; ++i) {
        relaxHeights(heights);
    }

    return heights;
}

std::vector<std::vector<float>> MapGenerator::getInitialHeights(int rows, int columns) {
    std::vector<std::vector<float>> heights(rows, std::vector<float>(columns));

    double centerRow = rows / 2.0;
    double centerColumn = columns / 2.0;

    int normalizator = rows + columns;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            const float manhattan = (fabs(centerRow - r) + fabs(centerColumn - c));

            heights[r][c] = -1 - 15 * manhattan / normalizator;
        }
    }

    return heights;
}

void MapGenerator::relaxHeights(std::vector<std::vector<float>>& heights) {
    std::vector<std::vector<float>> delta(heights.size(), std::vector<float>(heights[0].size(), 0));

    for (unsigned r = 0; r < heights.size(); ++r) {
        for (unsigned c = 0; c < heights[r].size(); ++c) {
            if (r != heights.size() - 1) {
                delta[r][c] += calculateDelta(heights[r][c], heights[r + 1][c]);
                delta[r + 1][c] -= calculateDelta(heights[r][c], heights[r + 1][c]);
            }
            if (c != heights[r].size() - 1) {
                delta[r][c] += calculateDelta(heights[r][c], heights[r][c + 1]);
                delta[r][c + 1] -= calculateDelta(heights[r][c], heights[r][c + 1]);
            }
        }
    }

    for (unsigned r = 0; r < heights.size(); ++r) {
        for (unsigned c = 0; c < heights[r].size(); ++c) {
            heights[r][c] += delta[r][c];
        }
    }
}

float MapGenerator::calculateDelta(float lhs, float rhs) {
    const double relaxationFactor = 0.1;
    return (rhs - lhs) * relaxationFactor;
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
