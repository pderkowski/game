/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Board.hpp"

Board::Board(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo),
    tilesVisibility_(rowsNo, std::vector<bool>(columnsNo, true)),
    tiles_(rowsNo, std::vector<Tile>(columnsNo, Tile()))
{ }

void Board::toggleVisibility(int row, int column) {
    tilesVisibility_[row][column] = !tilesVisibility_[row][column];
}

bool Board::isVisible(int row, int column) const {
    return tilesVisibility_[row][column];
}

int Board::getRowsNo() const {
    return rowsNo_;
}

int Board::getColumnsNo() const {
    return columnsNo_;
}
