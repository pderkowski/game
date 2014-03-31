/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Map.hpp"

Map::Map(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo),
    tilesVisibility_(rowsNo, std::vector<bool>(columnsNo, true)),
    tiles_(rowsNo, std::vector<Tile>(columnsNo, Tile()))
{ }

void Map::toggleVisibility(int row, int column) {
    tilesVisibility_[row][column] = !tilesVisibility_[row][column];
}

bool Map::isVisible(int row, int column) const {
    return tilesVisibility_[row][column];
}

int Map::getRowsNo() const {
    return rowsNo_;
}

int Map::getColumnsNo() const {
    return columnsNo_;
}
