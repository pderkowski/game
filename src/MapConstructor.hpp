/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPCONSTRUCTOR_HPP_
#define MAPCONSTRUCTOR_HPP_

#include <random>
#include <vector>
#include <utility>
#include "MapModel.hpp"
#include "Tile.hpp"

class MapConstructor {
private:
    struct Cell {
        enum Type {
            Unmarked,
            Water,
            Land
        };

        unsigned row;
        unsigned column;
        Type type;
    };

public:
    MapConstructor(unsigned rows, unsigned columns);
    void spawnContinent(unsigned continentSize);
    MapModel getMapModel() const;

private:
    std::pair<unsigned, unsigned> findContinentCenter(unsigned diameter);
    std::vector<Cell*> findContinentSeeds(unsigned numberOfSeeds, unsigned diameter);
    Cell* findSeed(const std::pair<unsigned, unsigned>& center, unsigned diameter);
    void markCell(Cell* cell, Cell::Type type);
    void markCells(const std::vector<Cell*>& cells, Cell::Type type);
    std::vector<Cell*> findNeighbors(const std::vector<Cell*>& cells);
    std::vector<Cell*> findNeighbors(const Cell* cell);
    bool isUnmarked(const Cell* cell) const;
    void removeMarked(std::vector<Cell*>& cells);
    Cell* chooseCell(std::vector<Cell*>& border);

    void assignTileTypes(MapModel& model) const;
    Tile::Type convertCellTypeToTileType(Cell::Type type) const;

    unsigned rows_;
    unsigned columns_;
    std::vector<std::vector<Cell>> map_;

    std::default_random_engine generator_;
};

#endif  // MAPCONSTRUCTOR_HPP_
