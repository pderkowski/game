/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>
#include "MapModel.hpp"
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "Gradient.hpp"
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

MapModel::MapModel(const HeightMap& heightMap, HeightToTileConverter converter)
    : MapModel(heightMap.getRowsNo(), heightMap.getColumnsNo())
{
    for (int r = 0; r < rowsNo_; ++r) {
        for (int c = 0; c < columnsNo_; ++c) {
           tiles_[r][c]->type = converter(heightMap(r, c));
        }
    }
}

MapModel::MapModel(const HeightMap& heightMap, const Gradient& gradient)
    : MapModel(heightMap.getRowsNo(), heightMap.getColumnsNo())
{
    auto cells = heightMap.getListOfCells();
    std::sort(cells.begin(), cells.end(),
        [] (const std::tuple<unsigned, unsigned, double>& lhs,
            const std::tuple<unsigned, unsigned, double>& rhs)
        { return std::get<2>(lhs) < std::get<2>(rhs); });

    for (unsigned cell = 0; cell < cells.size(); ++cell) {
        double gradientPoint = static_cast<double>(cell) / cells.size();
        tiles_[std::get<0>(cells[cell])][std::get<1>(cells[cell])]->type
            = gradient.getValue(gradientPoint);
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

std::shared_ptr<const Tile> MapModel::getTile(const IntIsoPoint& p) const {
    if (!isInBounds(p)) {
        throw std::range_error("Requested tile is out of range.");
    }
    return tiles_[p.y][utils::positiveModulo(p.x, columnsNo_)];
}

std::shared_ptr<Tile> MapModel::getTile(const IntIsoPoint& p) {
    return std::const_pointer_cast<Tile>(static_cast<const MapModel&>(*this).getTile(p));
}

std::vector<std::shared_ptr<const Tile>> MapModel::getNeighbors(std::shared_ptr<const Tile> tile) const {
    std::vector<IntRotPoint> neighborsCoords = {
        IntRotPoint(tile->coords.x, tile->coords.y - 1),
        IntRotPoint(tile->coords.x + 1, tile->coords.y - 1),
        IntRotPoint(tile->coords.x + 1, tile->coords.y),
        IntRotPoint(tile->coords.x + 1, tile->coords.y + 1),
        IntRotPoint(tile->coords.x, tile->coords.y + 1),
        IntRotPoint(tile->coords.x - 1, tile->coords.y + 1),
        IntRotPoint(tile->coords.x - 1, tile->coords.y),
        IntRotPoint(tile->coords.x - 1, tile->coords.y - 1) };

    std::vector<std::shared_ptr<const Tile>> neighbors;
    for (const auto& rotCoord : neighborsCoords) {
        IntIsoPoint isoCoord(rotCoord.toIsometric());
        if (isInBounds(isoCoord)) {
            neighbors.push_back(getTile(isoCoord));
        } else {
            auto dummy = std::make_shared<const Tile>(IntRotPoint(-1, -1));
            neighbors.push_back(dummy);
        }
    }

    return neighbors;
}

