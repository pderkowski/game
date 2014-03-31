/* Copyright 2014 <Piotr Derkowski> */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "Tile.hpp"

class Board {
public:
    Board(int rowsNo, int columnsNo);

    void toggleVisibility(int row, int column);
    bool isVisible(int row, int column) const;

    int getRowsNo() const;
    int getColumnsNo() const;

    static const int OutOfBounds = -1;

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<bool>> tilesVisibility_;
    std::vector<std::vector<Tile>> tiles_;
};

#endif  // BOARD_H_
