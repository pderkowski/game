/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <functional>
#include "HeightMap.hpp"

HeightMap::HeightMap(unsigned rowsNo, unsigned columnsNo)
    : rowsNo_(rowsNo), columnsNo_(columnsNo), map_(rowsNo, std::vector<double>(columnsNo))
{ }

const std::vector<double>& HeightMap::operator[] (unsigned row) const {
    return map_[row];
}

std::vector<double>& HeightMap::operator[] (unsigned row) {
    return map_[row];
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
