/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include "HeightMap.hpp"

HeightMap::HeightMap(unsigned rowsNo, unsigned columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo), map_(rowsNo, std::vector<double>(columnsNo))
{ }

const double& HeightMap::operator() (unsigned row, unsigned column) const {
    return map_[row][column];
}

double& HeightMap::operator() (unsigned row, unsigned column) {
    return map_[row][column];
}

HeightMap& HeightMap::foreach(std::function<double(double)> transformation) {
    for (auto& row : map_) {
        for (auto& cell : row) {
            cell = transformation(cell);
        }
    }
    return *this;
}

unsigned HeightMap::getRowsNo() const {
    return rowsNo_;
}

unsigned HeightMap::getColumnsNo() const {
    return columnsNo_;
}

std::vector<std::tuple<unsigned, unsigned, double>> HeightMap::getListOfCells() const {
    std::vector<std::tuple<unsigned, unsigned, double>> listOfCells;

    for (unsigned r = 0; r < rowsNo_; ++r) {
        for (unsigned c = 0; c < columnsNo_; ++c) {
            listOfCells.push_back(std::make_tuple(r, c, map_[r][c]));
        }
    }

    return listOfCells;
}
