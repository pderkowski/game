/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include "Tile.hpp"

class Map {
public:
    Map(int rowsNo, int columnsNo);

    void toggleVisibility(int row, int column);
    bool isVisible(int row, int column) const;

    int getRowsNo() const;
    int getColumnsNo() const;

    const Tile& tile(int row, int column) const;
    Tile& tile(int row, int column);

    static const int OutOfBounds = -1;

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<bool>> tilesVisibility_;
    std::vector<std::vector<Tile>> tiles_;
};

#endif  // MAP_HPP_
