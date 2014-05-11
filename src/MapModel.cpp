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

MapModel::MapModel(int rowsNo, int columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo)
{
    for (int r = 0; r < rowsNo; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int c = 0; c < columnsNo; ++c) {
            tiles_[r].push_back(std::make_shared<Tile>(r, c));
        }
    }
}

MapModel::MapModel(const HeightMap& heightMap, HeightToTileConverter converter)
    : rowsNo_(heightMap.getRowsNo()), columnsNo_(heightMap.getColumnsNo())
{
    for (int r = 0; r < rowsNo_; ++r) {
        tiles_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int c = 0; c < columnsNo_; ++c) {
            std::cout << heightMap[r][c] << "\n";
            Tile t = Tile(r, c, converter(heightMap[r][c]));
            tiles_[r].push_back(std::make_shared<Tile>(t));
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

std::shared_ptr<const Tile> MapModel::getTile(int row, int column) const {
    return tiles_[row][column];
}

std::shared_ptr<Tile> MapModel::getTile(int row, int column) {
    return tiles_[row][column];
}
