/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPCONSTRUCTOR_HPP_
#define MAPCONSTRUCTOR_HPP_

#include <random>
#include <vector>
#include <utility>
#include <memory>
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Pool.hpp"

class MapConstructor {
private:
    struct Cell {
        enum Type {
            Unmarked,
            Water,
            Land
        };

        int row;
        int column;
        Type type;
    };

public:
    MapConstructor(int rows, int columns,
        std::shared_ptr<std::default_random_engine> generator);
    void spawnContinent(unsigned continentSize);
    MapModel getMapModel() const;

private:
    Cell* findContinentSeed();
    Cell* getRandomCellCloseToCenter();
    void markCells(const std::vector<Cell*>& cells, Cell::Type type);
    std::vector<Cell*> findNeighbors(const std::vector<Cell*>& cells);
    std::vector<Cell*> findNeighbors(const Cell* cell);
    bool isUnmarked(const Cell* cell) const;
    void removeMarked(std::vector<Cell*>& cells);
    Pool<Cell> createBorder(const Cell* seed);

    void assignTileTypes(MapModel& model) const;
    Tile::Type convertCellTypeToTileType(Cell::Type type) const;

    int rows_;
    int columns_;
    std::vector<std::vector<Cell>> map_;
    HeightMap probabilityMap_;

    std::shared_ptr<std::default_random_engine> generator_;
};

#endif  // MAPCONSTRUCTOR_HPP_
