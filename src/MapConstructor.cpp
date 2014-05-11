/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include "MapConstructor.hpp"
#include "MapModel.hpp"
#include "NoiseGenerator.hpp"
#include "Tile.hpp"
#include "Pool.hpp"

MapConstructor::MapConstructor(unsigned rows, unsigned columns,
    std::shared_ptr<std::default_random_engine> generator)
        : rows_(rows), columns_(columns),
        map_(rows, std::vector<Cell>(columns)),
        probabilityMap_(
            NoiseGenerator::generateHeightMap(rows, columns, (*generator)())
                .foreach([] (double cell) { return 3 * cell; })
                .foreach([] (double cell) { return cell + 3; })
                .foreach([] (double cell) { return std::exp2(cell); })
                .foreach([] (double cell) { return std::round(cell); })),
        generator_(generator)
{
    for (unsigned r = 0; r < map_.size(); ++r) {
        for (unsigned c = 0; c < map_[r].size(); ++c) {
            map_[r][c].row = r;
            map_[r][c].column = c;
            map_[r][c].type = Cell::Type::Unmarked;
        }
    }
}

void MapConstructor::spawnContinent(unsigned continentSize) {
    auto seed = findContinentSeed();
    seed->type = Cell::Type::Land;
    auto border = createBorder(seed);
    int cellsToFind = continentSize - 1;

    while (cellsToFind > 0 && !border.isEmpty()) {
        auto cell = border.getRandom();
        border.remove(cell);
        cell->type = Cell::Type::Land;
        --cellsToFind;
        auto neighbors = findNeighbors(cell);
        removeMarked(neighbors);

        for (auto neighbor : neighbors) {
            if (border.contains(neighbor))
                border.setWeight(neighbor, 2 * border.getWeight(neighbor));
            else
                border.insert(neighbor, probabilityMap_[neighbor->row][neighbor->column]);
        }
    }

    markCells(border.toVector(), Cell::Type::Water);
}

MapConstructor::Cell* MapConstructor::findContinentSeed() {
    Cell* res = getRandomCellCloseToCenter();

    while (res->type != Cell::Type::Unmarked)
        res = getRandomCellCloseToCenter();

    return res;
}

MapConstructor::Cell* MapConstructor::getRandomCellCloseToCenter() {
    return &map_[(*generator_)() % (rows_ / 2) + (rows_ / 4)][(*generator_)() % columns_];
}

void MapConstructor::markCells(const std::vector<Cell*>& cells, Cell::Type type) {
    for (auto cell : cells)
        cell->type = type;
}

std::vector<MapConstructor::Cell*> MapConstructor::findNeighbors(const Cell* cell) {
    std::vector<Cell*> neighbors;

    if (cell->row > 0) {
        neighbors.push_back(&map_[cell->row - 1][cell->column]);
        neighbors.push_back(&map_[cell->row - 1][(cell->column + columns_ - 1) % columns_]);
        neighbors.push_back(&map_[cell->row - 1][(cell->column + columns_ + 1) % columns_]);
    }

    if (cell->row < rows_ - 1) {
        neighbors.push_back(&map_[cell->row + 1][cell->column]);
        neighbors.push_back(&map_[cell->row + 1][(cell->column + columns_ - 1) % columns_]);
        neighbors.push_back(&map_[cell->row + 1][(cell->column + columns_ + 1) % columns_]);
    }

    neighbors.push_back(&map_[cell->row][(cell->column + columns_ - 1) % columns_]);
    neighbors.push_back(&map_[cell->row][(cell->column + columns_ + 1) % columns_]);

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

Pool<MapConstructor::Cell> MapConstructor::createBorder(const Cell* seed) {
    Pool<Cell> border(generator_);

    auto neighbors = findNeighbors(seed);
    removeMarked(neighbors);

    for (auto neighbor : neighbors)
        border.insert(neighbor, probabilityMap_[neighbor->row][neighbor->column]);

    return border;
}


