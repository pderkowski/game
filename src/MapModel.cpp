/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include <algorithm>
#include "MapModel.hpp"
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "Coordinates.hpp"
#include "Utils.hpp"
#include "TileEnums.hpp"

MapModel::MapModel(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo), tiles_(rowsNo, std::vector<Tile>(columnsNo))
{
    for (int r = 0; r < rowsNo_; ++r) {
        for (int c = 0; c < columnsNo_; ++c) {
            tiles_[r][c] = Tile(IntRotPoint(IntIsoPoint(c, r).toRotated()), tileenums::Type::Empty, this);
        }
    }
}

MapModel::MapModel(const MapModel& other)
    : rowsNo_(other.rowsNo_), columnsNo_(other.columnsNo_),
    tiles_(other.rowsNo_, std::vector<Tile>(other.columnsNo_))
{
    for (int r = 0; r < rowsNo_; ++r) {
        for (int c = 0; c < columnsNo_; ++c) {
            tiles_[r][c] = Tile(other.tiles_[r][c]);
            tiles_[r][c].setModel(this);
        }
    }
}

MapModel::~MapModel() {
    setModelInTiles(nullptr);
}


void swap(MapModel& first, MapModel& other);

MapModel& MapModel::operator = (MapModel model) {
    swap(*this, model);
    return *this;
}

int MapModel::getRowsNo() const {
    return rowsNo_;
}

int MapModel::getColumnsNo() const {
    return columnsNo_;
}

bool MapModel::isInBounds(const IntIsoPoint& p) const {
    return 0 <= p.y && p.y < getRowsNo();
}


const Tile& MapModel::getTile(const IntIsoPoint& p) const {
    return tiles_[p.y][utils::positiveModulo(p.x, columnsNo_)];
}

Tile& MapModel::getTile(const IntIsoPoint& p) {
    return tiles_[p.y][utils::positiveModulo(p.x, columnsNo_)];
}

std::vector<Tile*> MapModel::getTiles(std::function<bool(Tile&)> selector) {
    std::vector<Tile*> res;

    for (auto& row : tiles_) {
        for (Tile& tile : row) {
            if (selector(tile)) {
                res.push_back(&tile);
            }
        }
    }

    return res;
}

void MapModel::changeTiles(std::function<void(Tile&)> transformation) {
    for (auto& row : tiles_) {
        for (Tile& tile : row) {
            transformation(tile);
        }
    }
}



void MapModel::setModelInTiles(MapModel* model) {
    for (auto& row : tiles_) {
        for (Tile& tile : row) {
            tile.setModel(model);
        }
    }
}

void swap(MapModel& first, MapModel& other) {
    std::swap(first.rowsNo_, other.rowsNo_);
    std::swap(first.columnsNo_, other.columnsNo_);
    std::swap(first.tiles_, other.tiles_);
    first.setModelInTiles(&first);
    other.setModelInTiles(&other);
}
