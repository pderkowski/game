/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <limits>
#include <vector>
#include <functional>
#include <algorithm>
#include "HeightMap.hpp"


namespace map {


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

unsigned HeightMap::getSize() const {
    return rowsNo_ * columnsNo_;
}

double HeightMap::min() const {
    double min = std::numeric_limits<double>::max();

    for (const auto& row : map_) {
        for (const auto& cell : row) {
            min = std::min(min, cell);
        }
    }

    return min;
}

double HeightMap::max() const {
    double max = std::numeric_limits<double>::min();

    for (const auto& row : map_) {
        for (const auto& cell : row) {
            max = std::max(max, cell);
        }
    }

    return max;
}

double HeightMap::getNth(unsigned n) const {
    if (n >= rowsNo_ * columnsNo_) {
        return max();
    } else {
        std::vector<double> heights;
        heights.reserve(getSize());

        for (const auto& row : map_) {
            for (const auto& cell : row) {
                heights.push_back(cell);
            }
        }

        std::sort(heights.begin(), heights.end());
        return heights[n];
    }
}


}  // namespace map
