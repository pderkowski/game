/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <tuple>
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
    : rowsNo_(rowsNo), columnsNo_(columnsNo)
{
    for (int r = 0; r < rowsNo; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>(columnsNo));
        for (int c = 0; c < columnsNo; ++c) {
            tiles_[r][c] = std::shared_ptr<Tile>(new Tile(IntRotPoint(IntIsoPoint(c, r).toRotated()),
                tileenums::Type::Empty, this));
        }
    }
}

MapModel::MapModel(const MapModel& other)
    : rowsNo_(other.rowsNo_), columnsNo_(other.columnsNo_), units_(other.units_)
{
    for (int r = 0; r < rowsNo_; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>(columnsNo_));
        for (int c = 0; c < columnsNo_; ++c) {
            tiles_[r][c] = std::shared_ptr<Tile>(new Tile(*(other.tiles_[r][c])));
            tiles_[r][c]->setModel(this);
        }
    }

    setModelInUnits(this);
}

MapModel::~MapModel() {
    setModelInTiles(nullptr);
    setModelInUnits(nullptr);
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

bool MapModel::isInBounds(std::shared_ptr<const Tile> tile) const {
    const IntIsoPoint coords(tile->coords.toIsometric());
    return isInBounds(coords);
}


std::shared_ptr<const Tile> MapModel::getTile(const IntIsoPoint& p) const {
    if (!isInBounds(p)) {
        return std::shared_ptr<const Tile>(new Tile(IntRotPoint(p.toRotated())));
    } else {
        return tiles_[p.y][utils::positiveModulo(p.x, columnsNo_)];
    }
}

std::shared_ptr<Tile> MapModel::getTile(const IntIsoPoint& p) {
    return std::const_pointer_cast<Tile>(static_cast<const MapModel&>(*this).getTile(p));
}

std::vector<std::shared_ptr<const Tile>> MapModel::getTilesByType(tileenums::Type type) const {
    std::vector<std::shared_ptr<const Tile>> res;

    for (const auto& row : tiles_) {
        for (const auto& tilePtr : row) {
            if (tilePtr->type == type) {
                res.push_back(tilePtr);
            }
        }
    }

    return res;
}

std::vector<std::shared_ptr<const Tile>> MapModel::getTiles(std::function<bool(const Tile&)> selector) const {
    std::vector<std::shared_ptr<const Tile>> res;

    for (const auto& row : tiles_) {
        for (const auto& tilePtr : row) {
            if (selector(*tilePtr)) {
                res.push_back(tilePtr);
            }
        }
    }

    return res;
}

void MapModel::changeTiles(std::function<void(Tile&)> transformation) {
    for (const auto& row : tiles_) {
        for (const auto& tilePtr : row) {
            transformation(*tilePtr);
        }
    }
}

void MapModel::addUnit(const units::Unit& unit) {
    units_.push_back(unit);
}

std::vector<units::Unit*> MapModel::getUnits() {
    std::vector<units::Unit*> res;

    for (auto& unit : units_) {
        res.push_back(&unit);
    }

    return res;
}

bool MapModel::doesPathExist(const Tile& source, const Tile& goal) const {
    return pathfinder_.doesPathExist(source, goal);
}

std::vector<tileenums::Direction> MapModel::findPath(const Tile& source, const Tile& goal) const {
    return pathfinder_.findPath(source, goal);
}


void MapModel::setModelInTiles(MapModel* model) {
    for (const auto& row : tiles_) {
        for (const auto& tilePtr : row) {
            tilePtr->setModel(model);
        }
    }
}

void MapModel::setModelInUnits(MapModel* model) {
    for (auto& unit : units_) {
        unit.setModel(model);
    }
}

void swap(MapModel& first, MapModel& other) {
    std::swap(first.rowsNo_, other.rowsNo_);
    std::swap(first.columnsNo_, other.columnsNo_);
    std::swap(first.units_, other.units_);
    std::swap(first.tiles_, other.tiles_);
    std::swap(first.pathfinder_, other.pathfinder_);
    first.setModelInTiles(&first);
    first.setModelInUnits(&first);
    other.setModelInTiles(&other);
    other.setModelInUnits(&other);
}
