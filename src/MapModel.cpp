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

MapModel::MapModel(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo)
{
    for (int r = 0; r < rowsNo; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>(columnsNo));
        for (int c = 0; c < columnsNo; ++c) {
            tiles_[r][c] = std::make_shared<Tile>(IntRotPoint(IntIsoPoint(c, r).toRotated()));
        }
    }
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
        throw std::range_error("Requested tile is out of range.");
    }
    return tiles_[p.y][utils::positiveModulo(p.x, columnsNo_)];
}

std::shared_ptr<Tile> MapModel::getTile(const IntIsoPoint& p) {
    return std::const_pointer_cast<Tile>(static_cast<const MapModel&>(*this).getTile(p));
}

std::vector<std::shared_ptr<const Tile>> MapModel::getTilesByType(Tile::Type type) const {
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

std::vector<std::shared_ptr<const Tile>> MapModel::getNeighbors(std::shared_ptr<const Tile> tile) const {
    return getNeighbors(*tile);
}

std::vector<std::shared_ptr<const Tile>> MapModel::getNeighbors(const Tile& tile) const {
    std::vector<IntRotPoint> neighborsCoords = {
        IntRotPoint(tile.coords.x, tile.coords.y - 1),
        IntRotPoint(tile.coords.x + 1, tile.coords.y - 1),
        IntRotPoint(tile.coords.x + 1, tile.coords.y),
        IntRotPoint(tile.coords.x + 1, tile.coords.y + 1),
        IntRotPoint(tile.coords.x, tile.coords.y + 1),
        IntRotPoint(tile.coords.x - 1, tile.coords.y + 1),
        IntRotPoint(tile.coords.x - 1, tile.coords.y),
        IntRotPoint(tile.coords.x - 1, tile.coords.y - 1) };

    std::vector<std::shared_ptr<const Tile>> neighbors;
    for (const auto& rotCoord : neighborsCoords) {
        IntIsoPoint isoCoord(rotCoord.toIsometric());
        if (isInBounds(isoCoord)) {
            neighbors.push_back(getTile(isoCoord));
        } else {
            auto dummy = std::make_shared<const Tile>(IntRotPoint(0, -1));
            neighbors.push_back(dummy);
        }
    }

    return neighbors;
}

std::vector<std::shared_ptr<const Tile>> MapModel::getAdjacentNeighbors(
    std::shared_ptr<const Tile> tile) const
{
    return getAdjacentNeighbors(*tile);
}

std::vector<std::shared_ptr<const Tile>> MapModel::getAdjacentNeighbors(const Tile& tile) const {
    std::vector<IntRotPoint> neighborsCoords = {
        IntRotPoint(tile.coords.x, tile.coords.y - 1),
        IntRotPoint(tile.coords.x + 1, tile.coords.y),
        IntRotPoint(tile.coords.x, tile.coords.y + 1),
        IntRotPoint(tile.coords.x - 1, tile.coords.y) };

    std::vector<std::shared_ptr<const Tile>> neighbors;
    for (const auto& rotCoord : neighborsCoords) {
        IntIsoPoint isoCoord(rotCoord.toIsometric());
        if (isInBounds(isoCoord)) {
            neighbors.push_back(getTile(isoCoord));
        } else {
            auto dummy = std::make_shared<const Tile>(IntRotPoint(0, -1));
            neighbors.push_back(dummy);
        }
    }

    return neighbors;
}

void MapModel::changeTiles(std::function<void(Tile&)> transformation) {
    for (const auto& row : tiles_) {
        for (const auto& tilePtr : row) {
            transformation(*tilePtr);
        }
    }
}
