/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Board.hpp"

Board::Board(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo), tiles_(rowsNo, std::vector<bool>(columnsNo, true))
{ }

void Board::toggleSelection(int row, int column) {
    tiles_[row][column] = !tiles_[row][column];
}

bool Board::isSelected(int row, int column) const {
    return tiles_[row][column];
}

int Board::getRowsNo() const {
    return rowsNo_;
}

int Board::getColumnsNo() const {
    return columnsNo_;
}
