/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include "MapConstructor.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Pool.hpp"

MapConstructor::MapConstructor(unsigned rows, unsigned columns,
    std::shared_ptr<std::default_random_engine> generator)
        : rows_(rows), columns_(columns),
        map_(rows, std::vector<Cell>(columns)),
        generator_(generator) {
    for (unsigned r = 0; r < map_.size(); ++r) {
        for (unsigned c = 0; c < map_[r].size(); ++c) {
            map_[r][c].row = r;
            map_[r][c].column = c;
            map_[r][c].type = Cell::Type::Unmarked;
        }
    }
}

void MapConstructor::spawnContinent(unsigned continentSize) {
    auto seeds = findContinentSeeds((*generator_)() % 3 + 2, sqrt(continentSize) / 2);
    markCells(seeds, Cell::Type::Land);
    auto border = createBorder(seeds);
    int cellsToFind = continentSize - seeds.size();

    while (cellsToFind > 0 && !border.isEmpty()) {
        auto cell = border.getRandom();
        border.remove(cell);
        cell->type = Cell::Type::Land;
        --cellsToFind;
        auto neighbors = findNeighbors(cell);
        removeMarked(neighbors);

        for (auto neighbor : neighbors)
            poolUtils::increaseWeight(border, neighbor);
    }

    markCells(border.toVector(), Cell::Type::Water);
}

std::vector<MapConstructor::Cell*> MapConstructor::findContinentSeeds(unsigned numberOfSeeds,
        unsigned diameter) {
    std::vector<MapConstructor::Cell*> seeds;

    auto center = findContinentCenter(diameter);

    for (unsigned i = 0; i < numberOfSeeds; ++i) {
        Cell* seed = findSeed(center, diameter);
        if (std::find(seeds.begin(), seeds.end(), seed) == seeds.end()) {
            seeds.push_back(seed);
        }
    }

    return seeds;
}

std::pair<unsigned, unsigned> MapConstructor::findContinentCenter(unsigned diameter) {
    unsigned row = rows_ / 2 + ((*generator_)() % (2 * diameter)) - diameter;
    unsigned col = ((*generator_)() % (columns_ - 2 * diameter)) + diameter;
    return std::make_pair(row, col);
}

MapConstructor::Cell* MapConstructor::findSeed(const std::pair<unsigned, unsigned>& center,
        unsigned diameter) {
    unsigned row = center.first + (*generator_)() % (2 * diameter) - diameter;
    unsigned col = center.second + (*generator_)() % (2 * diameter) - diameter;
    return &map_[row][col];
}

void MapConstructor::markCells(const std::vector<Cell*>& cells, Cell::Type type) {
    for (auto cell : cells)
        cell->type = type;
}

std::vector<MapConstructor::Cell*> MapConstructor::findNeighbors(const Cell* cell) {
    std::vector<Cell*> neighbors;

    if (cell->row > 0)
        neighbors.push_back(&map_[cell->row - 1][cell->column]);

    if (cell->row > 0 && cell->column > 0)
        neighbors.push_back(&map_[cell->row - 1][cell->column - 1]);

    if (cell->row > 0 && cell->column < columns_ - 1)
        neighbors.push_back(&map_[cell->row - 1][cell->column + 1]);

    if (cell->row < rows_ - 1)
        neighbors.push_back(&map_[cell->row + 1][cell->column]);

    if (cell->row < rows_ - 1 && cell->column > 0)
        neighbors.push_back(&map_[cell->row + 1][cell->column - 1]);

    if (cell->row < rows_ - 1 && cell->column < columns_ - 1)
        neighbors.push_back(&map_[cell->row + 1][cell->column + 1]);

    if (cell->column > 0)
        neighbors.push_back(&map_[cell->row][cell->column - 1]);

    if (cell->row < columns_ - 1)
        neighbors.push_back(&map_[cell->row][cell->column + 1]);

    return neighbors;
}

std::vector<MapConstructor::Cell*> MapConstructor::findNeighbors(const std::vector<Cell*>& cells) {
    std::vector<Cell*> neighbors;

    for (auto cell : cells) {
        auto thisCellNeighbors = findNeighbors(cell);
        neighbors.insert(neighbors.end(), thisCellNeighbors.begin(), thisCellNeighbors.end());
    }

    return neighbors;
}

bool MapConstructor::isUnmarked(const Cell* cell) const {
    return cell->type == Cell::Type::Unmarked;
}

void MapConstructor::removeMarked(std::vector<Cell*>& cells) {
    auto removedIt = std::remove_if(cells.begin(), cells.end(),
        [&](const Cell* cell) { return !isUnmarked(cell); }); //NOLINT
    cells.erase(removedIt, cells.end());
}

MapModel MapConstructor::getMapModel() const {
    MapModel model(rows_, columns_);
    assignTileTypes(model);
    return model;
}

void MapConstructor::assignTileTypes(MapModel& model) const {
    for (unsigned r = 0; r < rows_; ++r) {
        for (unsigned c = 0; c < columns_; ++c) {
            model.getTile(r, c)->type = convertCellTypeToTileType(map_[r][c].type);
        }
    }
}

Tile::Type MapConstructor::convertCellTypeToTileType(Cell::Type type) const {
    if (type == Cell::Type::Land) {
        return Tile::Type::Plains;
    } else {
        return Tile::Type::Water;
    }
}

Pool<MapConstructor::Cell> MapConstructor::createBorder(
        const std::vector<MapConstructor::Cell*>& seeds) {
    Pool<Cell> border(generator_);

    for (auto seed : seeds) {
        auto neighbors = findNeighbors(seed);
        removeMarked(neighbors);

        for (auto neighbor : neighbors)
            poolUtils::increaseWeight(border, neighbor);
    }

    return border;
}


