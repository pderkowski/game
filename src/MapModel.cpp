/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <memory>
#include "MapModel.hpp"
#include "Tile.hpp"
#include "noiseutils/noiseutils.h"

MapModel::MapModel(int rowsNo, int columnsNo)
        : rowsNo_(rowsNo), columnsNo_(columnsNo) {
    for (int r = 0; r < rowsNo; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int c = 0; c < columnsNo; ++c) {
            tiles_[r].push_back(std::make_shared<Tile>(r, c));
        }
    }
}

MapModel::MapModel(const HeightMap& heightMap, HeightToTileConverter converter)
        : rowsNo_(heightMap.GetHeight()), columnsNo_(heightMap.GetWidth()) {
    for (int r = 0; r < rowsNo_; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int c = 0; c < columnsNo_; ++c) {
            Tile t = Tile(r, c, converter(heightMap.GetValue(c, r)));
            tiles_[r].push_back(std::make_shared<Tile>(t));
        }
    }
}

int MapModel::getRowsNo() const {
    return rowsNo_;
}

int MapModel::getColumnsNo() const {
    return columnsNo_;
}

std::shared_ptr<const Tile> MapModel::getTile(int row, int column) const {
    return tiles_[row][column];
}

std::shared_ptr<Tile> MapModel::getTile(int row, int column) {
    return tiles_[row][column];
}
