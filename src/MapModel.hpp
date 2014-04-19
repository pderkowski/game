/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPMODEL_HPP_
#define MAPMODEL_HPP_

#include <vector>
#include <memory>
#include "Tile.hpp"

class MapModel {
public:
    MapModel(int rowsNo, int columnsNo);

    int getRowsNo() const;
    int getColumnsNo() const;

    std::shared_ptr<const Tile> getTile(int row, int column) const;
    std::shared_ptr<Tile> getTile(int row, int column);

    static const int OutOfBounds = -1;

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
};

#endif  // MAPMODEL_HPP_
